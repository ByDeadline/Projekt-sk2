import pygame
from threading import Timer
import socket
import sys
import textwrap
import random

SCREEN_WIDTH = 1000
SCREEN_HEIGHT = 1000
COLOR_LIGHT_BLUE = (0, 0, 255)
COLOR_DARK_BLUE = (0, 0, 128)
COLOR_GREY = (105, 105, 105)
COLOR_GREEN = (0, 255, 0)
RED = (255, 0, 0)
logged_in = False
timer = 100


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
    def get_rooms(self):
        # Possible statuses: Waiting, Playing
        rooms = {}
        if self.my_id == None:
            return rooms

        try:
            self.socket.send(("show_lobbies,"+self.my_id).encode())
        except:
            pass
        response = self.socket.recv(1024).decode()
        for room in response.split('\n'):
            if room != "":
                rooms[room.split(',')[0]] = [int(room.split(',')[1])]
        print(rooms)
        return rooms

    def send_join_room(self, room_name):
        # self.socket.send(room_name.encode())
        # response = self.socket.recv(1024).decode()
        response = "OK"
        if response == "OK":
            return True
        return False

    def get_game_string(self, room_name):
        # self.socket.send("get_game_string".encode())
        # game_string = self.socket.recv(1024).decode()
        game_string = "Lorem ipsum dolor sit amet. Id debitis ipsa vel commodi quos est aliquam sunt. Non omnis animi aut Quis neque et rerum numquam ut facilis doloribus eum suscipit rerum ut quia quia aut eaque adipisci."
        return game_string

    def send_letter(self, letter):
        # self.socket.send(letter.encode())

        self.sent_letters.append(letter)
        return True

    def set_name(self, name):
        msg = "login,"+"".join(name)
        self.socket.send(msg.encode())
        response = self.socket.recv(1024).decode()
        if response.split(',')[0] == "success":
            self.my_id = response.split(',')[1]
            return response.split(',')[1]
        return None

    def get_players_in_room(self):
        # self.socket.send("get_players_in_room".encode())
        # players = self.socket.recv(1024).decode()
        players = ["Player 1", "Player 2", "Player 3", "Player 4"]
        return players

    def get_players_progress(self, progress):
        players = self.get_players_in_room()
        progress = progress
        for player in players:
            # self.socket.send(("get_player_progress " + player).encode())
            # progress = self.socket.recv(1024).decode()
            progress[player] += 5
        return progress
    def leave_room(self):
        # self.socket.send("leave_room".encode())
        return True
    def player_ready(self):
        # self.socket.send("player_ready".encode())
        return True
    def player_unready(self):
        # self.socket.send("player_unready".encode())
        return True
    def send_word(self, word_length):
        # self.socket.send(("send_word " + word_length).encode())
        return True

class Room():
    def __init__(self, name, players,server):
        self.server = server
        self.TIME_TO_START = 100
        self.name = name
        self.players = players
        self.player_count = len(players)
        self.started = False
        self.ready_players = []

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
        if player in self.ready_players:
            if self.server.player_unready():
                self.ready_players.remove(player)
                return False
        if self.server.player_ready():
            self.ready_players.append(player)
        return True

    def player_unready(self, player):
        if player not in self.ready_players:
            return False
        self.ready_players.remove(player)
        return True


class Player():
    def __init__(self, name, server_communication, room=None ):
        self.name = name
        self.room = room
        self.server = server_communication
        self.my_id = None

    def join_room(self, room):
        if room.started:
            return False
        if room.player_count >= 4:
            return False
        self.room = room
        room.add_player(self)
        return True

    def set_name(self, name):
        self.my_id=self.server.set_name(name)
        if self.my_id != None:

            self.name = ''.join(name)
            return True
        return False


class Game():
    def __init__(self,server):
        self.server = server
        self.rooms = []
        self.players = []

    def create_room(self, name):
        room = Room(name, [],self.server)
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


class InputBox:
    def __init__(self, x, y, w, h, function_after_enter, text=[]):
        self.x = x
        self.y = y
        self.w = w
        self.h = h
        self.rect = pygame.Rect(x - w//2, y, w, h)
        self.visible_text = text
        self.function_after_enter = function_after_enter
        self.active = True
        self.color = COLOR_LIGHT_BLUE
        self.whole_text = ""
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
        self.rect = pygame.Rect(self.x - self.w//2, self.y, self.w, self.h)

    def draw(self, screen):
        self.txt_surface = pygame.font.Font(None, 32).render("".join(self.visible_text), True, self.color)
        # Blit the text.
        screen.blit(self.txt_surface, (self.rect.x + 5, self.rect.y + 10))
        # Blit the rect.
        pygame.draw.rect(screen, self.color, self.rect, 2)

    def get_text(self):
        return self.visible_text


def draw_room_list(screen, game, player,server):
    font_size = 15
    rooms = server.get_rooms()
    record_height = 40
    record_width = SCREEN_WIDTH - 20
    top_margin = 50
    text_margin = record_height // 2

    usr_icon = pygame.image.load("usr_icon.png")
    usr_icon = pygame.transform.scale(usr_icon, (30, 30))
    screen.blit(usr_icon, (10, 10))

    font = pygame.font.Font(None, 32)
    name_surface = font.render(''.join(player.name), True, (0, 0, 0))
    screen.blit(name_surface, (50, 10))

    for i in range(len(rooms)):
        room = rooms[i]
        pygame.draw.rect(screen, COLOR_GREY, (10,top_margin + record_height * i, record_width, record_height), 2, 3)
        font = pygame.font.Font('freesansbold.ttf', font_size)
        text = font.render(room.name, True, COLOR_DARK_BLUE)
        textRect = text.get_rect()
        textRect.center = (50, text_margin + top_margin + record_height * i)
        screen.blit(text, textRect)
        text = font.render(str(room.player_count) + "/4", True, COLOR_DARK_BLUE)
        textRect = text.get_rect()
        textRect.center = (record_width - 30, 75 + record_height * i)
        screen.blit(text, textRect)


def draw_player_name_input(screen, input_box):
    font = pygame.font.Font('freesansbold.ttf', 32)
    text = font.render('Enter your name', True, COLOR_DARK_BLUE)
    textRect = text.get_rect()
    textRect.center = (SCREEN_WIDTH // 2, SCREEN_HEIGHT // 2)
    screen.blit(text, textRect)
    input_box.draw(screen)
    pygame.display.flip()
def draw_room(screen, room):

    red_check = pygame.image.load("red_check.png")
    red_check = pygame.transform.scale(red_check, (30, 30))
    green_check = pygame.image.load("green_check.jpg")
    green_check = pygame.transform.scale(green_check, (30, 30))

    players = room.players

    font_size = 20
    record_height = 50
    top_margin = SCREEN_HEIGHT // 2 - record_height * room.player_count // 2
    text_margin = record_height // 2

    rdy_button = pygame.rect.Rect(SCREEN_WIDTH // 2-45, SCREEN_HEIGHT - 100, 90, 30)
    pygame.draw.rect(screen, COLOR_GREEN, rdy_button)
    font = pygame.font.Font('freesansbold.ttf', 20)
    text = font.render('Ready', True, COLOR_DARK_BLUE)
    textRect = text.get_rect()
    textRect.center = (SCREEN_WIDTH // 2, SCREEN_HEIGHT - 85)
    screen.blit(text, textRect)
    for i in range(len(players)):
        player = players[i].name
        pygame.draw.rect(screen, COLOR_GREY, (10, top_margin + record_height * i, SCREEN_WIDTH - 20, record_height), 2,3)

        text = font.render(player, True, COLOR_DARK_BLUE)
        textRect = text.get_rect()
        textRect.center = (SCREEN_WIDTH // 2, text_margin + top_margin + record_height * i)
        screen.blit(text, textRect)

        if player in room.ready_players:
            screen.blit(green_check, (SCREEN_WIDTH - 50, text_margin + top_margin + record_height * i - 15))
        else:
            screen.blit(red_check, (SCREEN_WIDTH - 50, text_margin + top_margin + record_height * i - 15))




    font = pygame.font.Font('freesansbold.ttf', font_size)
    text = font.render(room.name, True, COLOR_DARK_BLUE)
    textRect = text.get_rect()
    textRect.center = (SCREEN_WIDTH // 2, 200)
    screen.blit(text, textRect)

def draw_game(screen, game, server,cars,input_box,game_string):


    font_size = 20
    left_margin = 50
    top_margin = 100
    car_margin = 100
    screen.blit(cars[0], (left_margin, top_margin))
    screen.blit(cars[1], (left_margin, top_margin + car_margin))
    screen.blit(cars[2], (left_margin, top_margin + car_margin * 2))
    screen.blit(cars[3], (left_margin, top_margin + car_margin * 3))


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
            screen.blit(text, (left_margin + text_width, SCREEN_HEIGHT//2 + line * 20))
            text_width += 3+ text.get_width()
            text_index+=1
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
    game = Game(server)
    player = Player("", server)


    #test


    blue_car = pygame.image.load("blue_car.png")
    blue_car = pygame.transform.scale(blue_car, (100, 100))
    red_car = pygame.image.load("red_car.png")
    red_car = pygame.transform.scale(red_car, (100, 100))
    white_car = pygame.image.load("white_car.png")
    white_car = pygame.transform.scale(white_car, (100, 100))
    black_car = pygame.image.load("black_car.png")
    black_car = pygame.transform.scale(black_car, (100, 100))
    cars = [blue_car, red_car, white_car, black_car]

    input_box_name = InputBox(SCREEN_WIDTH // 2 , (SCREEN_HEIGHT // 2) + 50, 140, 32, player.set_name)
    input_box_answer = InputBox(SCREEN_WIDTH // 2, SCREEN_HEIGHT - 400, 400, 32, server.send_letter)
    while True:

        # Fill the background with white
        screen.fill((255, 255, 255))
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
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
                        rooms = game.get_rooms()
                        for i in range(len(rooms)):
                            room = rooms[i]
                            if 10 < mouse_pos[0] < SCREEN_WIDTH - 10 and 50 + 40 * i < mouse_pos[1] < 90 + 40 * i:
                                if player.join_room(room):
                                    game_string = server.get_game_string(room.name)
                                    logged_in = True
                                    break
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
                            player.room.remove_player(player)
                            player.room = None
                            break
                    if event.type == pygame.MOUSEBUTTONDOWN:
                        if event.button == 1:
                            mouse_pos = event.pos
                            print(mouse_pos)
                            if SCREEN_WIDTH // 2 - 45 < mouse_pos[0] < SCREEN_WIDTH // 2 + 45 and SCREEN_HEIGHT - 100 < mouse_pos[1] < SCREEN_HEIGHT - 70:
                                if player.room.player_ready(player.name):
                                    print("ready")
                                else:
                                    player.room.player_unready(player.name)
                                    print("unready")

                # Handle game events
                else:
                    if event.type == pygame.KEYDOWN:
                        if event.key == pygame.K_ESCAPE:
                            player.room.remove_player(player)
                            player.room = None
                            break
                        if event.key == pygame.K_SPACE:
                            print(input_box_answer.whole_text,game_string)
                            if input_box_answer.whole_text in game_string:
                                if server.send_word(len(input_box_answer.whole_text.split())):
                                    input_box_answer.visible_text = []
                                    input_box_answer.whole_text+=" "
                                    input_box_answer.draw(screen)
                        else:
                            input_box_answer.handle_event(event)

        # Draw the game

        # Draw login screen
        if not logged_in:
            draw_player_name_input(screen, input_box_name)
            if player.name != "":
                logged_in = True

        # Draw room list
        elif player.room == None:
            draw_room_list(screen, game,player)

        # Draw room and game
        elif player.room != None:

            # Draw game
            if player.room.started:
                draw_game(screen, game, server,cars,input_box_answer,game_string)

            # Draw room
            else:
                draw_room(screen, player.room)
                if len(player.room.ready_players) == player.room.player_count and player.room.player_count > 1:
                    player.room.start_game()
                    game.start_game(player.room)

        pygame.display.flip()


if __name__ == '__main__':
    pygame.init()
    main(logged_in)
