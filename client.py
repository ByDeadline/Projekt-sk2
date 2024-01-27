import fcntl
import os
import pygame
import socket
import textwrap
import threading
import time
SCREEN_WIDTH = 1000
SCREEN_HEIGHT = 1000
COLOR_LIGHT_BLUE = (0, 0, 255)
COLOR_DARK_BLUE = (0, 0, 128)
COLOR_GREY = (105, 105, 105)
COLOR_GREEN = (0, 255, 0)
RED = (255, 0, 0)
logged_in = False
timer = 100
global game_string
game_string = ""
global game_started
game_started = False

def wrap_string(string, max_width):

    return textwrap.wrap(string, max_width)


class ServerCommunication:
    def __init__(self, ip, port):

        self.ip = ip
        self.port = port
        self.sent_letters = []
        self.socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.socket.connect((self.ip, self.port))
        self.my_id = None
        self.my_room_id = None
        self.connected = True

    def set_name(self, name):
        msg = "login," + "".join(name)+" "
        self.socket.send(msg.encode())
        time.sleep(0.1)
        response = self.socket.recv(1024).decode()
        if "ok" in response:
            response = self.socket.recv(1024).decode()
        if response.split(',')[0] == "success":
            self.my_id = response.split(',')[1:][0]
            print(self.my_id)
            print("logged in")
            return response.split(',')[1:]

        return None

    def get_rooms(self, game):
        rooms = {}
        if self.my_id == None:
            return rooms
        msg = "show_lobbies," + self.my_id+ " "
        self.socket.send(msg.encode())
        time.sleep(0.1)
        response = self.socket.recv(1024).decode()
        room_names = game.get_names_of_rooms()
        if "success" in response:
            response = response.replace('success,', '')

            for room in response.split('\n'):
                if room != "":
                    rooms[room.split(',')[0]] = room.split(',')[1]
                    if room.split(',')[0] not in room_names:
                        game.create_room(room.split(',')[0])
            return rooms


    def create_room(self):
        self.socket.send(("create_lobby," + self.my_id + " ").encode())
        time.sleep(0.1)
        response = self.socket.recv(1024).decode()
        response = response.split('\n')
        print("created room with this res",response)
        if "success" in response[-1]:
            room = response[-1].split(',')[1]
            print("created room", room)
            self.my_room_id = room
            return response
        return None

    def send_join_room(self, room_name):
        self.socket.send(("join_lobby," + self.my_id + "," + room_name + " ").encode())
        time.sleep(0.1)
        response = self.socket.recv(1024).decode()
        response = response.split('\n')
        if "success" in response[-1]:
            self.my_room_id = room_name
            print("joined room")
            response.pop(-1)
            return response
        return None

    def update_rooms(self, update_room,player):

        #dodac sprawdzanie czy status jest w odpowiedzi i jesli nie to nie updateowac

        fcntl.fcntl(self.socket, fcntl.F_SETFL, os.O_NONBLOCK)
        try:
            response = self.socket.recv(1024).decode()
            if "text" in response:
                global game_string
                player.room.started = True
                game_string = response.split("\n")[-1].split(',')[2]
                global gama_string_length
                game_string_length = response.split("\n")[-1].split(',')[1]
                return
            if "status" in response:
                update_room(response.split('\n'))

        except:
            pass
        finally:
            # Set the socket back to blocking mode
            fcntl.fcntl(self.socket, fcntl.F_SETFL, 0)
    def update_game(self,room):

        #dodac sprawdzanie czy status jest w odpowiedzi i jesli nie to nie updateowac

        fcntl.fcntl(self.socket, fcntl.F_SETFL, os.O_NONBLOCK)
        try:
            response = self.socket.recv(1024).decode()

            response = response.split('\n')

            print("response",response)
            print("response[0]",response[0])
            if "status" in response[0].split(","):
                room.progress = {}
                print("udalo")
                players = response

                for player in players:
                    player = player.replace('status,', '')
                    print("player",player)
                    room.update_progress(player.split(',')[0], int(player.split(',')[1]))
                print("room progress",room.progress)
        except:
            raise
        finally:
            # Set the socket back to blocking mode
            fcntl.fcntl(self.socket, fcntl.F_SETFL, 0)
    def send_disconnect(self):
        self.socket.send(("disconnect," + self.my_id + " ").encode())
        self.socket.close()
        self.connected = False


    def player_ready(self, player):
        print("player name", player.name, "room name", player.room.name)
        self.socket.send(("ready," + self.my_id + "," + player.room.name + " ").encode())
        return True

    def send_progress(self, prog):
        self.socket.send(("progress," + self.my_id + "," + self.my_room_id + "," + prog+" ").encode())
        return True



def send_alive(quit,socket,my_id):
    while not quit.is_set():
        socket.send(("alive,"+my_id+" ").encode())
        time.sleep(10)

    print("quit")


class Room():
    def __init__(self, name, players, server):
        self.server = server
        self.TIME_TO_START = 100
        self.name = name
        self.players = players
        self.player_count = len(players)
        self.started = False
        self.ready_players = []
        self.progress = {}

    def add_player(self, player):
        self.players.append(player)
        self.player_count += 1

    def remove_player(self, player):
        if self.server.leave_room():
            self.players.remove(player)
            self.player_count -= 1

    def start_game(self):
        self.started = True

    def player_ready(self, player):
        if self.server.player_ready(player):
            self.ready_players.append(player.name)
            return True
        return False

    def player_unready(self, player):
        if player not in self.ready_players:
            return False
        self.ready_players.remove(player)
        return True
    def unpack_players(self, msg):
        self.players = []
        print("got this msg to unpack",msg)
        if isinstance(msg, str):
            msg = msg.replace('status,', '')
            self.players.append(Player(msg.split(',')[0], self.server, self))
            self.player_count += 1
            if msg[1] == "y":
                self.ready_players.append(msg.split(',')[0])
            return
        for player in msg:
            if "$" not in player and player != "":
                player = player.replace('status,', '')
                self.players.append(Player(player.split(',')[0], self.server, self))
                self.player_count += 1
                if player.split(',')[1] == "y":
                    self.ready_players.append(player.split(',')[0])
        print("unpacked players",self.players)
        self.players.sort(key=lambda x: x.name)
    def start_game(self):
        for player in self.players:
            self.progress[player.name] = 0
    def update_progress(self, player_name, progress):
        print("updating progress",player_name,progress)
        self.progress[player_name] = progress

class Player():
    def __init__(self, name, server_communication, room=None):
        self.name = name
        self.room = room
        self.server = server_communication
        self.my_id = None
        self.logged_in = False
        self.ready = False

    def join_room(self, room):
        if room.started:
            return False
        if room.player_count >= 4:
            return False
        self.res = self.server.send_join_room(room.name)
        if self.res is not None:
            self.room = room
            room.add_player(self)
            room.unpack_players(self.res)
        return True
    def create_room(self):
        self.res = self.server.create_room()
        if self.res is not None:
            self.room = Room(self.res[1].split(',')[1], [], self.server)
            self.room.add_player(self)
            self.room.unpack_players(self.res[0])
        return True
    def set_name(self, name):
        self.my_id = self.server.set_name(name)
        if self.my_id != None:
            self.name = ''.join(name)
            return True
        return False


class Game():
    def __init__(self, server):
        self.server = server
        self.rooms = []
        self.players = []

    def create_room(self, name):
        room = Room(name, [], self.server)
        self.rooms.append(room)

    def join_room(self, player, room):
        if player.join_room(room):
            return True
        return False

    def remove_player(self, player):
        room = player.room
        room.remove_player(player)
        if room.player_count == 0:
            self.rooms.remove(room)

    def start_game(self, room):
        room.start_game()

    def get_rooms(self):
        return self.rooms

    def get_names_of_rooms(self):
        names = []
        for room in self.rooms:
            names.append(room.name)
        return names

    def get_room_by_name(self, name):
        for room in self.rooms:
            if room.name == name:
                return room
        return None


class InputBox:
    def __init__(self, x, y, w, h, function_after_enter = None, text=[], is_enter_blocked=False):
        self.x = x
        self.y = y
        self.w = w
        self.h = h
        self.rect = pygame.Rect(x - w // 2, y, w, h)
        self.visible_text = text
        self.function_after_enter = function_after_enter
        self.active = True
        self.color = COLOR_LIGHT_BLUE
        self.whole_text = ""
        self.is_enter_blocked = is_enter_blocked
        if self.active:
            self.color = COLOR_LIGHT_BLUE
        else:
            self.color = COLOR_DARK_BLUE
        self.txt_surface = pygame.font.Font(None, 32).render("".join(self.visible_text), True, self.color)

    def handle_event(self, event):
        if event.type == pygame.MOUSEBUTTONDOWN:
            # If the user clicked on the input_box rect.
            if self.rect.collidepoint(event.pos):
                self.active = True
                self.color = COLOR_LIGHT_BLUE
            else:
                self.color = COLOR_DARK_BLUE
            # Change the current color of the input box.
            self.txt_surface = pygame.font.Font(None, 32).render("".join(self.visible_text), True, self.color)
        if event.type == pygame.KEYDOWN:
            if self.active:
                if event.key == pygame.K_RETURN:
                    if not self.is_enter_blocked:
                        self.function_after_enter(self.visible_text)
                        self.visible_text = []
                        self.whole_text = ""

                elif event.key == pygame.K_BACKSPACE:
                    if len(self.visible_text) > 0 and len(self.whole_text) > 0:
                        if self.visible_text[-1] == self.whole_text[-1]:
                            self.whole_text = self.whole_text[:-1]
                        self.visible_text.pop()
                else:
                    if len(self.visible_text) >= 9:
                        self.update(0, 0, 10)
                    self.visible_text.append(event.unicode)
                    self.whole_text += event.unicode
                # Re-render the text.
                self.txt_surface = pygame.font.Font(None, 32).render("".join(self.visible_text), True, self.color)
        self.draw(screen)

    def update(self, x=0, y=0, w=0, h=0):
        # Resize the box.
        self.x += x
        self.y += y
        self.w += w
        self.h += h
        self.rect = pygame.Rect(self.x - self.w // 2, self.y, self.w, self.h)

    def draw(self, screen):
        self.txt_surface = pygame.font.Font(None, 32).render("".join(self.visible_text), True, self.color)
        # Blit the text.
        screen.blit(self.txt_surface, (self.rect.x + 5, self.rect.y + 10))
        # Blit the rect.
        pygame.draw.rect(screen, self.color, self.rect, 2)

    def get_text(self):
        return self.visible_text


def draw_room_list(screen, game, player, server, rooms):
    font_size = 15
    record_height = 40
    record_width = SCREEN_WIDTH - 20
    top_margin = 50
    text_margin = record_height // 2

    usr_icon = pygame.image.load("usr_icon.png")
    usr_icon = pygame.transform.scale(usr_icon, (30, 30))
    screen.blit(usr_icon, (10, 10))

    # create room button
    create_room_button = pygame.rect.Rect(SCREEN_WIDTH - 150, SCREEN_HEIGHT - 40, 140, 30)
    pygame.draw.rect(screen, COLOR_GREEN, create_room_button)
    font = pygame.font.Font('freesansbold.ttf', 20)
    text = font.render('Create room', True, COLOR_DARK_BLUE)
    textRect = text.get_rect()
    textRect.center = (SCREEN_WIDTH - 80, SCREEN_HEIGHT - 25)
    screen.blit(text, textRect)

    if isinstance(rooms, dict):
        global rooms_copy
        rooms_copy = rooms.copy()

    font = pygame.font.Font(None, 32)
    name_surface = font.render(''.join(player.name), True, (0, 0, 0))
    screen.blit(name_surface, (50, 10))
    i = 0
    for room in rooms:
        pygame.draw.rect(screen, COLOR_GREY, (10, top_margin + record_height * i, record_width, record_height), 2, 3)
        font = pygame.font.Font('freesansbold.ttf', font_size)
        try:
            text = font.render(room, True, COLOR_DARK_BLUE)
            textRect = text.get_rect()
            textRect.center = (50, text_margin + top_margin + record_height * i)
            screen.blit(text, textRect)
            text = font.render(str(rooms[room]) + "/4", True, COLOR_DARK_BLUE)
            textRect = text.get_rect()
            textRect.center = (record_width - 30, 75 + record_height * i)
            screen.blit(text, textRect)
        except:
            text = font.render(room.name, True, COLOR_DARK_BLUE)
            textRect = text.get_rect()
            textRect.center = (50, text_margin + top_margin + record_height * i)
            screen.blit(text, textRect)
            text = font.render(str(rooms_copy[room.name]) + "/4", True, COLOR_DARK_BLUE)
            textRect = text.get_rect()
            textRect.center = (record_width - 30, 75 + record_height * i)
            screen.blit(text, textRect)
        i += 1
    #draw refresh button
    refresh_button = pygame.rect.Rect(SCREEN_WIDTH - 150, SCREEN_HEIGHT - 80, 140, 30)
    pygame.draw.rect(screen, COLOR_GREEN, refresh_button)
    font = pygame.font.Font('freesansbold.ttf', 20)
    text = font.render('Refresh', True, COLOR_DARK_BLUE)
    textRect = text.get_rect()
    textRect.center = (SCREEN_WIDTH - 80, SCREEN_HEIGHT - 65)
    screen.blit(text, textRect)

def draw_player_name_input(screen, input_box):
    font = pygame.font.Font('freesansbold.ttf', 32)
    text = font.render('Enter your name', True, COLOR_DARK_BLUE)
    textRect = text.get_rect()
    textRect.center = (SCREEN_WIDTH // 2, SCREEN_HEIGHT // 2)
    screen.blit(text, textRect)
    input_box.draw(screen)
    pygame.display.flip()


def draw_room(screen, room, server,cars):
    red_check = pygame.image.load("red_check.png")
    red_check = pygame.transform.scale(red_check, (30, 30))
    green_check = pygame.image.load("green_check.jpg")
    green_check = pygame.transform.scale(green_check, (30, 30))

    players = room.players

    font_size = 20
    record_height = 50
    top_margin = SCREEN_HEIGHT // 2 - record_height * room.player_count // 2
    text_margin = record_height // 2

    rdy_button = pygame.rect.Rect(SCREEN_WIDTH // 2 - 45, SCREEN_HEIGHT - 100, 90, 30)
    pygame.draw.rect(screen, COLOR_GREEN, rdy_button)
    font = pygame.font.Font('freesansbold.ttf', 20)
    text = font.render('Ready', True, COLOR_DARK_BLUE)
    textRect = text.get_rect()
    textRect.center = (SCREEN_WIDTH // 2, SCREEN_HEIGHT - 85)
    screen.blit(text, textRect)
    for i in range(len(players)):
        player = players[i].name
        pygame.draw.rect(screen, COLOR_GREY, (10, top_margin + record_height * i, SCREEN_WIDTH - 20, record_height), 2,
                         3)

        text = font.render(player, True, COLOR_DARK_BLUE)
        textRect = text.get_rect()
        textRect.center = (SCREEN_WIDTH // 2, text_margin + top_margin + record_height * i)
        screen.blit(text, textRect)
        if player in room.ready_players:
            screen.blit(green_check, (SCREEN_WIDTH - 50, text_margin + top_margin + record_height * i - 15))
        else:
            screen.blit(red_check, (SCREEN_WIDTH - 50, text_margin + top_margin + record_height * i - 15))

        #draw coresponding car

        screen.blit(cars[i], (SCREEN_WIDTH - 200, text_margin + top_margin + record_height * (i-1)))


    font = pygame.font.Font('freesansbold.ttf', font_size)
    text = font.render(room.name, True, COLOR_DARK_BLUE)
    textRect = text.get_rect()
    textRect.center = (SCREEN_WIDTH // 2, 200)
    screen.blit(text, textRect)


def draw_game(screen, game, server, cars, input_box,room):
    font_size = 20
    left_margin = 50
    top_margin = 100
    car_margin = 100
    for i in range(len(room.players)):
        screen.blit(cars[i], (left_margin, top_margin + car_margin * i))
    font = pygame.font.Font('freesansbold.ttf', font_size)
    wrapped_string = wrap_string(game_string, 70)
    text_width = 0
    line = 0

    text_index = 0

    text_input = input_box
    for i in range(len(wrapped_string)):
        for j in range(len(wrapped_string[i])):
            if text_index < len(input_box.whole_text):
                if game_string[text_index] == input_box.whole_text[text_index]:
                    text = font.render(wrapped_string[i][j], True, COLOR_GREEN)
                else:
                    text = font.render(wrapped_string[i][j], True, RED)
            else:
                text = font.render(wrapped_string[i][j], True, COLOR_DARK_BLUE)
            screen.blit(text, (left_margin + text_width, SCREEN_HEIGHT // 2 + line * 20))
            text_width += 3 + text.get_width()
            text_index += 1
        text_width = 0
        line += 1
    text_input.draw(screen)


# Set up the drawing window
screen = pygame.display.set_mode([SCREEN_HEIGHT, SCREEN_WIDTH], )


def main(logged_in=False):
    try:
        server = ServerCommunication("localhost", 1234)
    except:
        print("Server not found")
        exit()

    quitEvent = threading.Event()

    game = Game(server)
    player = Player("", server)
    rooms_to_show = {}
    cars = []
    blue_car = pygame.image.load("blue_car.png")
    blue_car = pygame.transform.scale(blue_car, (100, 100))
    red_car = pygame.image.load("red_car.png")
    red_car = pygame.transform.scale(red_car, (100, 100))
    white_car = pygame.image.load("white_car.png")
    white_car = pygame.transform.scale(white_car, (100, 100))
    black_car = pygame.image.load("black_car.png")
    black_car = pygame.transform.scale(black_car, (100, 100))
    cars = [blue_car, red_car, white_car, black_car]

    input_box_name = InputBox(SCREEN_WIDTH // 2, (SCREEN_HEIGHT // 2) + 50, 140, 32, player.set_name)
    input_box_answer = InputBox(SCREEN_WIDTH // 2, SCREEN_HEIGHT - 200, 400, 32, is_enter_blocked=True)


    thread_started = False
    while True:

        # Fill the background with white
        screen.fill((255, 255, 255))
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                server.send_disconnect()
                print("disconnected")
                quitEvent.set()
                pygame.quit()
                exit()
            # Handle user name input events
            if not logged_in:
                input_box_name.handle_event(event)

            # Handle room list events
            if logged_in and player.room == None:
                input_box_answer.visible_text = []
                input_box_answer.whole_text = ""
                input_box_name.visible_text = []
                input_box_name.whole_text = ""
                if event.type == pygame.MOUSEBUTTONDOWN:
                    if event.button == 1:
                        mouse_pos = event.pos
                        rooms_to_show = game.get_rooms()
                        for i in range(len(rooms_to_show)):
                            room = rooms_to_show[i]
                            if 10 < mouse_pos[0] < SCREEN_WIDTH - 10 and 50 + 40 * i < mouse_pos[1] < 90 + 40 * i:
                                if player.join_room(room):

                                    logged_in = True
                                    break
                                print("didnt join room")
                                rooms_to_show = server.get_rooms(game)

                        if SCREEN_WIDTH - 150 < mouse_pos[0] < SCREEN_WIDTH - 10 and SCREEN_HEIGHT - 40 < mouse_pos[
                            1] < SCREEN_HEIGHT - 10:
                            if player.create_room():
                                rooms_to_show = server.get_rooms(game)
                        if SCREEN_WIDTH - 150 < mouse_pos[0] < SCREEN_WIDTH - 10 and SCREEN_HEIGHT - 80 < mouse_pos[
                            1] < SCREEN_HEIGHT - 50:
                            rooms_to_show = server.get_rooms(game)
                if event.type == pygame.KEYDOWN:
                    if event.key == pygame.K_ESCAPE:
                        logged_in = False
                        player.room = None
                        player.name = ""
                        break

            # Handle room events
            if logged_in and player.room != None:
                if not player.room.started:
                    if event.type == pygame.KEYDOWN:
                        if event.key == pygame.K_ESCAPE:
                            rooms_to_show = server.get_rooms(game)
                            player.room.remove_player(player)
                            player.room = None
                            break
                    if event.type == pygame.MOUSEBUTTONDOWN:
                        if event.button == 1:
                            mouse_pos = event.pos

                            # check if player clicked ready button
                            if SCREEN_WIDTH // 2 - 45 < mouse_pos[0] < SCREEN_WIDTH // 2 + 45 and SCREEN_HEIGHT - 100 < \
                                    mouse_pos[1] < SCREEN_HEIGHT - 70:
                                if player.room.player_ready(player):
                                    print("ready")
                                else:
                                    player.room.player_unready(player)
                                    print("unready")

                # Handle game events
                else:
                    if event.type == pygame.KEYDOWN:
                        if event.key == pygame.K_ESCAPE:
                            rooms_to_show = server.get_rooms(game)
                            player.room.remove_player(player)
                            player.room = None
                            break
                        if event.key == pygame.K_SPACE:

                            if input_box_answer.whole_text.split(" ") == game_string.split(" ")[
                                                                         0:len(input_box_answer.whole_text.split(" "))]:
                                if server.send_progress(str(len(input_box_answer.whole_text.split()))):
                                    input_box_answer.visible_text = []
                                    input_box_answer.whole_text += " "
                                    input_box_answer.draw(screen)
                        else:
                            input_box_answer.handle_event(event)

        # Draw the game

        # Draw login screen
        if not logged_in:
            draw_player_name_input(screen, input_box_name)
            if player.name != "":
                rooms_to_show = server.get_rooms(game)
                logged_in = True

        # Draw room list
        elif player.room == None:
            if not thread_started:

                t = threading.Thread(target=send_alive, args=(quitEvent ,server.socket, server.my_id))
                t.start()
                thread_started = True
            draw_room_list(screen, game, player, server, rooms_to_show)

        # Draw room and game
        elif player.room != None:

            # Draw game
            if player.room.started:
                server.update_game(player.room)
                draw_game(screen, game, server, cars, input_box_answer,player.room)

            # Draw room
            else:
                server.update_rooms(player.room.unpack_players,player)
                draw_room(screen, player.room,server,cars)
                if len(player.room.ready_players) == player.room.player_count and player.room.player_count > 1:
                    player.room.start_game()
                    game.start_game(player.room)

        pygame.display.flip()


if __name__ == '__main__':
    pygame.init()
    main(logged_in)
