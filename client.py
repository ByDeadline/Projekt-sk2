import fcntl
import os
import pygame
import socket
import textwrap
import threading
import time

SCREEN_WIDTH = 800
SCREEN_HEIGHT = 800
COLOR_LIGHT_BLUE = (0, 0, 255)
COLOR_DARK_BLUE = (0, 0, 128)
COLOR_GREY = (105, 105, 105)
COLOR_GREEN = (0, 255, 0)
RED = (255, 0, 0)

logged_in = False
global game_string
game_string = ""

global game_started
game_started = False

failed_to_login = False

is_an_admin = False
admin_btn_clicked = False

red_check = pygame.image.load("assets/red_check.png")
red_check = pygame.transform.scale(red_check, (30, 30))
green_check = pygame.image.load("assets/green_check.jpg")
green_check = pygame.transform.scale(green_check, (30, 30))
usr_icon = pygame.image.load("assets/usr_icon.png")
usr_icon = pygame.transform.scale(usr_icon, (30, 30))

def wrap_string(string, max_width):
    wraped_string = textwrap.wrap(string, max_width)
    for i in range(len(wraped_string)):
        wraped_string[i] += " "
    return wraped_string


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
        msg = "login," + "".join(name) + " "
        try:
            self.socket.send(msg.encode())
            time.sleep(0.1)
            response = self.socket.recv(1024).decode()
            if response.split(',')[0] == "success":
                self.my_id = response.split(',')[1:][0]
                print("logged in")
                return response.split(',')[1:]
            return None
        except:
            print("server not found")
            exit()
    def login_admin(self, name):
        global is_an_admin

        self.socket.send(("admin," + "".join(name) + " ").encode())
        time.sleep(0.1)
        response = self.socket.recv(1024).decode()
        if response.split(',')[0] == "success":
            self.my_id = response.split(',')[1:][0]
            is_an_admin = True
            print("logged in as admin")
            return response.split(',')[1:]
        return None
    def get_users(self,game):
        try:
            users = {}
            msg = "show_users," + self.my_id + " "
            self.socket.send(msg.encode())
            time.sleep(0.1)
            response = self.socket.recv(1024).decode()
            if "success" in response:
                response = response.replace('success,', '')
                for user in response.split('\n'):
                    if user != "":
                        user = user.split(',')
                        if user[0] not in game.get_players():
                            game.add_player(user[0])
        except:
            print("server not found")
            exit()
    def kick_user(self, user):
        return True
    def get_rooms(self, game):
        try:
            rooms = {}
            if self.my_id == None:
                return rooms
            msg = "show_lobbies," + self.my_id + " "
            self.socket.send(msg.encode())
            time.sleep(0.1)
            response = self.socket.recv(1024).decode()
            room_names = game.get_names_of_rooms()
            if "success" in response:
                response = response.replace('success,', '')

                for room in response.split('\n'):
                    if room != "":
                        room = room.split(',')

                        if "y" not in room[2]:
                            rooms[room[0]] = room[1]
                            if room[0] not in room_names:
                                game.create_room(room[0])
                return rooms
        except:
            print("server not found")
            exit()

    def create_room(self):
        try:
            self.socket.send(("create_lobby," + self.my_id + " ").encode())
            time.sleep(0.1)
            response = self.socket.recv(1024).decode()
            response = response.split('\n')
            print("created room with this res", response)
            if "success" in response[-1]:
                room = response[-1].split(',')[1]
                print("created room", room)
                self.my_room_id = room
                return response
            return None
        except:
            print("server not found")
            exit()

    def send_join_room(self, room_name):
        try:
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
        except:
            print("server not found")
            exit()

    def send_leave_room(self):
        try:
            self.socket.send(("leave_lobby," + self.my_id + "," + self.my_room_id + " ").encode())
            time.sleep(0.1)
            response = self.socket.recv(1024).decode()
            response = response.split('\n')
            if "success" in response[-1]:
                print("left room")
                response.pop(-1)
                return True
            return False
        except:
            print("server not found")
            exit()

    def update_rooms(self, update_room, player):
        fcntl.fcntl(self.socket, fcntl.F_SETFL, os.O_NONBLOCK)
        try:
            response = self.socket.recv(1024).decode()
            if "text" in response:
                global game_string
                player.room.started = True
                game_string = response.split("\n")[-1].split(',')[2]
                return
            if "status" in response:
                update_room(response.split('\n'))

        except:
            pass
        finally:
            # Set the socket back to blocking mode
            fcntl.fcntl(self.socket, fcntl.F_SETFL, 0)

    def update_game(self, room):
        fcntl.fcntl(self.socket, fcntl.F_SETFL, os.O_NONBLOCK)
        try:
            response = self.socket.recv(1024).decode()
            response = response.split('\n')
            for x in response:
                if "finish" in x.split(","):
                    print("finished")
                    room.end_game()
            if "status" in response[0].split(","):
                room.progress = {}
                players = response

                for player in players:
                    if player != "":
                        player = player.replace('status,', '')
                        print("player", player)
                        room.update_progress(player.split(',')[0], int(player.split(',')[1]))

        except:
            pass
        finally:
            # Set the socket back to blocking mode
            fcntl.fcntl(self.socket, fcntl.F_SETFL, 0)

    def send_disconnect(self):
        self.socket.send(("logout," + self.my_id + " ").encode())
        self.socket.close()
        self.connected = False

    def player_ready(self, player):
        self.socket.send(("ready," + self.my_id + "," + player.room.name + " ").encode())
        return True

    def send_progress(self, prog):
        self.socket.send(("progress," + self.my_id + "," + self.my_room_id + "," + prog + " ").encode())
        return True


def send_alive(quit, socket, my_id):
    while not quit.is_set():
        socket.send(("alive," + my_id + " ").encode())
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
        self.game_end = False

    def add_player(self, player):
        self.players.append(player)
        self.player_count += 1

    def remove_player(self, player):
        pass

    def start_game(self):
        self.started = True

    def player_ready(self, player):
        if player.name not in self.ready_players:
            if self.server.player_ready(player):
                if player.name not in self.ready_players:
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
        print("got this msg to unpack", msg)
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
                self.update_progress(player.split(',')[0], 0)
        print("unpacked players", self.players)
        self.players.sort(key=lambda x: x.name)

    def start_game(self):
        for player in self.players:
            self.progress[player.name] = 0

    def update_progress(self, player_name, progress):
        print("updating progress", player_name, progress)
        self.progress[player_name] = progress

    def end_game(self):
        self.game_end = True


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

    def leave_room(self):
        if self.server.send_leave_room():
            self.room.remove_player(self)
            self.room = None
            return True
        return False

    def set_name(self, name):
        global admin_btn_clicked
        if admin_btn_clicked:
            self.my_id = self.server.login_admin(name)
        else:
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

    def add_player(self, player):
        self.players.append(player)

    def remove_player(self, player):
        self.players.remove(player)

    def get_players(self):
        return self.players

    def refresh_players(self):
        self.players = []
        self.server.get_users(self)

class InputBox:
    def __init__(self, x, y, w, h, function_after_enter=None, text=[], is_enter_blocked=False):

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
        global failed_to_login
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
                        if self.function_after_enter(self.visible_text):
                            failed_to_login = False
                            self.visible_text = []
                            self.whole_text = ""
                        else:
                            failed_to_login = True

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
    global usr_icon
    font_size = 15
    record_height = 40
    record_width = SCREEN_WIDTH - 20
    top_margin = 50
    text_margin = record_height // 2

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
    # draw refresh button
    refresh_button = pygame.rect.Rect(SCREEN_WIDTH - 150, SCREEN_HEIGHT - 80, 140, 30)
    pygame.draw.rect(screen, COLOR_GREEN, refresh_button)
    font = pygame.font.Font('freesansbold.ttf', 20)
    text = font.render('Refresh', True, COLOR_DARK_BLUE)
    textRect = text.get_rect()
    textRect.center = (SCREEN_WIDTH - 80, SCREEN_HEIGHT - 65)
    screen.blit(text, textRect)


def draw_player_name_input(screen, input_box):
    global red_check, green_check, admin_btn_clicked
    font = pygame.font.Font('freesansbold.ttf', 32)
    text = font.render('Enter your name', True, COLOR_DARK_BLUE)
    textRect = text.get_rect()
    textRect.center = (SCREEN_WIDTH // 2, SCREEN_HEIGHT // 2)
    screen.blit(text, textRect)
    input_box.draw(screen)

    # draw admin button
    admin_button = pygame.rect.Rect(SCREEN_WIDTH // 2 - 45, SCREEN_HEIGHT // 2 + 100, 90, 30)
    pygame.draw.rect(screen, COLOR_GREEN, admin_button)
    font = pygame.font.Font('freesansbold.ttf', 20)
    text = font.render('Admin', True, COLOR_DARK_BLUE)
    textRect = text.get_rect()
    textRect.center = (SCREEN_WIDTH // 2, SCREEN_HEIGHT // 2 + 115)
    screen.blit(text, textRect)
    if admin_btn_clicked:
        screen.blit(green_check, (SCREEN_WIDTH // 2 + 50, SCREEN_HEIGHT // 2 + 100))
    else:
        screen.blit(red_check, (SCREEN_WIDTH // 2 + 50, SCREEN_HEIGHT // 2 + 100))
    if failed_to_login:
        font = pygame.font.Font('freesansbold.ttf', 20)
        text = font.render('Name already taken', True, RED)
        textRect = text.get_rect()
        textRect.center = (SCREEN_WIDTH // 2, SCREEN_HEIGHT // 2 + 100)
        screen.blit(text, textRect)

    pygame.display.flip()


def draw_room(screen, room, cars):
    global red_check
    global green_check
    players = room.players

    font_size = 20
    record_height = 50
    top_margin = SCREEN_HEIGHT // 2 - record_height * len(players) // 2
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

        # draw coresponding car

        screen.blit(cars[i], (SCREEN_WIDTH - 200, text_margin + top_margin + record_height * (i - 1)))

    font = pygame.font.Font('freesansbold.ttf', font_size)
    text = font.render(room.name, True, COLOR_DARK_BLUE)
    textRect = text.get_rect()
    textRect.center = (SCREEN_WIDTH // 2, 200)
    screen.blit(text, textRect)


def draw_game(screen, cars, input_box, room, player):
    font_size = 20
    left_margin = 50
    right_margin = 50
    top_margin = 100
    car_margin = 100
    track = SCREEN_WIDTH - left_margin - right_margin * 2
    for i in range(len(room.players)):
        screen.blit(cars[i], (left_margin + track * room.progress[room.players[i].name] / len(game_string.split(" ")),
                              top_margin + car_margin * i))
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
    if room.game_end:
        screen.fill((255, 255, 255))
        lider_board = list(dict(sorted(room.progress.items(), key=lambda item: item[1])).keys())
        font = pygame.font.Font('freesansbold.ttf', 30)

        text = font.render("Game finished " + "First place: " + str(lider_board[-1]), True, COLOR_DARK_BLUE)
        textRect = text.get_rect()
        textRect.center = (SCREEN_WIDTH // 2, SCREEN_HEIGHT // 2)
        screen.blit(text, textRect)
        pygame.display.flip()
        time.sleep(5)
        player.room = None


def draw_admin_panel(screen,game,player):
    record_height = 40
    record_width = SCREEN_WIDTH - 20
    top_margin = 50
    text_margin = record_height // 2

    screen.blit(usr_icon, (10, 10))
    font = pygame.font.Font(None, 32)
    name_surface = font.render(''.join(player.name), True, (0, 0, 0))
    screen.blit(name_surface, (50, 10))

    players = game.get_players()
    for i in range(len(players)):
        pygame.draw.rect(screen, COLOR_GREY, (10, top_margin + record_height * i, record_width, record_height), 2,
                         3)
        font = pygame.font.Font('freesansbold.ttf', 20)
        text = font.render(players[i], True, COLOR_DARK_BLUE)
        textRect = text.get_rect()
        textRect.center = (50, text_margin + top_margin + record_height * i)
        screen.blit(text, textRect)
        # draw kick button
        kick_button = pygame.rect.Rect(SCREEN_WIDTH - 100, top_margin + record_height * i + 5, 50, 30)
        pygame.draw.rect(screen, RED, kick_button)
        font = pygame.font.Font('freesansbold.ttf', 20)
        text = font.render('Kick', True, COLOR_DARK_BLUE)
        textRect = text.get_rect()
        textRect.center = (SCREEN_WIDTH - 75, text_margin + top_margin + record_height * i)
        screen.blit(text, textRect)



# Set up the drawing window
screen = pygame.display.set_mode([SCREEN_HEIGHT, SCREEN_WIDTH], )


def main():
    try:
        server = ServerCommunication("localhost", 1234)
    except:
        print("Server not found")
        exit()

    quitEvent = threading.Event()
    global logged_in,admin_btn_clicked
    game = Game(server)
    player = Player("", server)
    rooms_to_show = {}


    blue_car = pygame.image.load("assets/blue_car.png")
    blue_car = pygame.transform.scale(blue_car, (100, 100))
    red_car = pygame.image.load("assets/red_car.png")
    red_car = pygame.transform.scale(red_car, (100, 100))
    white_car = pygame.image.load("assets/white_car.png")
    white_car = pygame.transform.scale(white_car, (100, 100))
    black_car = pygame.image.load("assets/black_car.png")
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
                if logged_in:
                    server.send_disconnect()
                print("disconnected")
                quitEvent.set()
                pygame.quit()
                exit()
            # Handle user name input events
            if not logged_in:
                input_box_name.handle_event(event)
                if event.type == pygame.MOUSEBUTTONDOWN:
                    if event.button == 1:
                        mouse_pos = event.pos
                        # check if player clicked admin button
                        if (SCREEN_WIDTH // 2 - 45 < mouse_pos[0] < SCREEN_WIDTH // 2 + 45 and SCREEN_HEIGHT // 2 + 100 < \
                                mouse_pos[1] < SCREEN_HEIGHT // 2 + 130):
                            admin_btn_clicked = not admin_btn_clicked
            # Handle admin panel events
            if logged_in and is_an_admin:
                if event.type == pygame.MOUSEBUTTONDOWN:
                    if event.button == 1:
                        mouse_pos = event.pos
                        players = game.get_players()
                        for i in range(len(players)):
                            # check if player clicked kick button for player i
                            if (SCREEN_WIDTH - 100 < mouse_pos[0] < SCREEN_WIDTH - 50 and 50 + 40 * i < mouse_pos[1] <
                                    80 + 40 * i):
                                if server.kick_user(players[i]):
                                    game.remove_player(players[i])
                                    game.refresh_players()
                                    break
            # Handle room list events
            if logged_in and player.room == None and not is_an_admin:
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
                            # check if player clicked join button for room i
                            if 10 < mouse_pos[0] < SCREEN_WIDTH - 10 and 50 + 40 * i < mouse_pos[1] < 90 + 40 * i:
                                if player.join_room(room):
                                    logged_in = True
                                    break
                                print("didnt join room")
                                rooms_to_show = server.get_rooms(game)

                        if (SCREEN_WIDTH - 150 < mouse_pos[0] < SCREEN_WIDTH - 10 and SCREEN_HEIGHT - 40 < mouse_pos[1] <
                                SCREEN_HEIGHT - 10):
                            if player.create_room():
                                rooms_to_show = server.get_rooms(game)
                        if (SCREEN_WIDTH - 150 < mouse_pos[0] < SCREEN_WIDTH - 10 and SCREEN_HEIGHT - 80 < mouse_pos[1] <
                                SCREEN_HEIGHT - 50):
                            rooms_to_show = server.get_rooms(game)

            # Handle room events
            if logged_in and player.room != None:
                if not player.room.started:
                    if event.type == pygame.KEYDOWN:
                        if event.key == pygame.K_ESCAPE:
                            player.leave_room()
                            rooms_to_show = server.get_rooms(game)

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
                            player.leave_room()
                        if event.key == pygame.K_SPACE:

                            if input_box_answer.whole_text.split(" ") == game_string.split(" ")[
                                                                         0:len(input_box_answer.whole_text.split(" "))]:
                                if server.send_progress(str(len(input_box_answer.whole_text.split(" ")))):
                                    input_box_answer.visible_text = []
                                    input_box_answer.whole_text += " "
                                    input_box_answer.draw(screen)
                        else:
                            input_box_answer.handle_event(event)

        # Draw

        # Draw login screen
        if not logged_in:
            draw_player_name_input(screen, input_box_name)
            if player.name != "":
                rooms_to_show = server.get_rooms(game)
                logged_in = True
                if is_an_admin:
                    game.refresh_players()

        # Draw room list
        elif player.room == None:
            if not thread_started:
                t = threading.Thread(target=send_alive, args=(quitEvent, server.socket, server.my_id))
                t.start()
                thread_started = True
            if is_an_admin:
                draw_admin_panel(screen,game,player)
            else:
                draw_room_list(screen, game, player, server, rooms_to_show)

        # Draw room and game
        elif player.room != None:

            # Draw game
            if player.room.started:
                server.update_game(player.room)
                draw_game(screen, cars, input_box_answer, player.room, player)

            # Draw room
            else:
                server.update_rooms(player.room.unpack_players, player)
                draw_room(screen, player.room, cars)
                if len(player.room.ready_players) == player.room.player_count and player.room.player_count > 1:
                    player.room.start_game()
                    game.start_game(player.room)

        pygame.display.flip()


if __name__ == '__main__':
    pygame.init()
    main()
