import pygame
from threading import Timer
import socket


SCREEN_WIDTH = 1000
SCREEN_HEIGHT = 1000
COLOR_LIGHT_BLUE = (0, 0, 255)
COLOR_DARK_BLUE = (0, 0, 128)
COLOR_GREY = (105, 105, 105)
logged_in = False
timer = 100

class ServerCommunication:
    def __init__(self,ip, port):

        self.ip = ip
        self.port = port
        """self.socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.socket.connect((self.ip, self.port))"""
    def get_rooms(self):
        # Possible statuses: Waiting, Playing


        '''self.socket.send("get_rooms_count".encode())
        rooms_count = self.socket.recv(1024).decode()
        rooms_list = []
        rooms = {}
        for x in range(rooms_count):
            self.socket.send("get_room".encode())
            rooms_list.append(socket.recv(1024).decode())
        for x in rooms_list:
            rooms[x]=[]
            self.socket.send(("get_players_count "+ x).encode())
            rooms[x].append(socket.recv(1024).decode())
            self.socket.send(("get_room_status "+ x).encode())
            rooms[x].append(socket.recv(1024).decode())'''
        rooms = {
            "Room 1": [2,"Waiting"],
            "Room 2": [3,"Waiting"],
            "Room 3": [4,"Playing"],
            "Room 4": [1,"Waiting"]
        }
        return rooms
    def send_join_room(self,room_name):
        #self.socket.send(room_name.encode())
        #response = self.socket.recv(1024).decode()
        response = "OK"
        if response == "OK":
            return True
        return False
    def get_game_string(self):
        #self.socket.send("get_game_string".encode())
        #game_string = self.socket.recv(1024).decode()
        game_string = "Lorem ipsum dolor sit amet."
        return game_string
    def send_letter(self,letter):
        #self.socket.send(letter.encode())
        pass
    def set_name(self,name):
        #self.socket.send(name.encode())
        return True
    def get_players_in_room(self):
        #self.socket.send("get_players_in_room".encode())
        #players = self.socket.recv(1024).decode()
        players = ["Player 1","Player 2","Player 3","Player 4"]
        return players
    def get_players_progress(self,progress):
        players = self.get_players_in_room()
        progress = progress
        for player in players:
            #self.socket.send(("get_player_progress " + player).encode())
            #progress = self.socket.recv(1024).decode()
            progress[player] += 5
        return progress



class FunctionRepeter:
    def __init__(self, interval, function, *args, **kwargs):
        self._timer = None
        self.interval = interval
        self.function = function
        self.args = args
        self.kwargs = kwargs
        self.is_running = False
        self.start()

    def _run(self):
        self.is_running = False
        self.start()
        self.function(*self.args, **self.kwargs)

    def start(self):
        if not self.is_running:
            self._timer = Timer(self.interval, self._run)
            self._timer.start()
            self.is_running = True

    def stop(self):
        self._timer.cancel()
        self.is_running = False

class Room():
    def __init__(self, name, players):
        self.TIME_TO_START = 100
        self.name = name
        self.players = players
        self.player_count = len(players)
        self.started = False
        self.ready_players = []
    def add_player(self,player):
        self.players.append(player)
        self.player_count += 1
    def remove_player(self,player):
        self.players.remove(player)
        self.player_count -= 1
    def start_game(self):
        self.started = True
    def player_ready(self,player):
        if player in self.ready_players:
            return False
        self.ready_players.append(player)
        return True
    def player_unready(self,player):
        if player not in self.ready_players:
            return False
        self.ready_players.remove(player)
        return True
class Player():
    def __init__(self, name,server_communication, room = None,):
        self.name = name
        self.room = room
        self.server = server_communication
    def join_room(self, room):
        if room.started:
            return False
        if room.player_count >= 4:
            return False
        self.room = room
        room.add_player(self.name)
        return True
    def set_name(self,name):
        if self.server.set_name(name):
            self.name = name
            return True
        return False



class Game():
    def __init__(self):
        self.rooms = []
        self.players = []
    def create_room(self, name):
        room = Room(name, [])
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
    def __init__(self, x, y, w, h, function_after_enter,text=[]):
        self.rect = pygame.Rect(x, y, w, h)
        self.text = text
        self.function_after_enter = function_after_enter
        self.active = True
        self.color = COLOR_LIGHT_BLUE
        if self.active:
            self.color = COLOR_LIGHT_BLUE
        else:
            self.color = COLOR_DARK_BLUE
        self.txt_surface = pygame.font.Font(None, 32).render("".join(self.text), True, self.color)
        self.cursor = pygame.Rect(self.txt_surface.get_rect().bottomleft, (3, self.txt_surface.get_height()))

    def handle_event(self, event):
        if event.type == pygame.MOUSEBUTTONDOWN:
            # If the user clicked on the input_box rect.
            if self.rect.collidepoint(event.pos):
                self.active = True
                self.color = COLOR_LIGHT_BLUE
            else:
                self.color = COLOR_DARK_BLUE
            # Change the current color of the input box.
            self.txt_surface = pygame.font.Font(None, 32).render("".join(self.text), True, self.color)
        if event.type == pygame.KEYDOWN:
            if self.active:
                if event.key == pygame.K_RETURN:
                    self.function_after_enter(self.text)
                    self.text = []
                elif event.key == pygame.K_BACKSPACE:
                    print(self.text)
                    self.text = self.text.pop()
                else:
                    if len(self.text) >= 9:
                        self.update()
                    print(event.unicode)
                    self.text.append(event.unicode)
                # Re-render the text.
                self.txt_surface = pygame.font.Font(None, 32).render("".join(self.text), True, self.color)
                # bounding rectangle of the text
                text_rect = self.txt_surface.get_rect(topleft=(self.rect.x + 5, self.rect.y + 10))
                # set cursor position
                self.cursor.midleft = text_rect.midright

    def update(self):
        # Resize the box if the text is too long.
        width = max(200, self.txt_surface.get_width()+10)
        self.rect.move_ip(-10,0)
        self.rect.w = width
    def draw(self, screen):
        # Blit the text.
        screen.blit(self.txt_surface, (self.rect.x+5, self.rect.y+10))
        # Blit the rect.
        pygame.draw.rect(screen, self.color, self.rect, 2)
    def get_text(self):
        return self.text
def draw_room_list(screen,game):
    font_size = 15
    rooms = game.get_rooms()
    record_height = 40
    record_width = SCREEN_WIDTH - 20
    for i in range(len(rooms)):
        room = rooms[i]
        pygame.draw.rect(screen, COLOR_GREY, (10, 10 + record_height * i, record_width, record_height),2,3)
        font = pygame.font.Font('freesansbold.ttf', font_size)
        text = font.render(room.name, True, COLOR_DARK_BLUE)
        textRect = text.get_rect()
        textRect.center = (50,25 + record_height * i)
        screen.blit(text, textRect)
        text = font.render(str(room.player_count) + "/4", True, COLOR_DARK_BLUE)
        textRect = text.get_rect()
        textRect.center = (record_width - 30,25 + record_height * i)
        screen.blit(text, textRect)

def draw_player_name_input(screen,input_box):
    font = pygame.font.Font('freesansbold.ttf', 32)
    text = font.render('Enter your name', True, COLOR_DARK_BLUE)
    textRect = text.get_rect()
    textRect.center = (SCREEN_WIDTH // 2, SCREEN_HEIGHT // 2)
    screen.blit(text, textRect)
    input_box.draw(screen)
    pygame.display.flip()
class GameHandler():
    def __init__(self,player):
        self.room_name = player.room.name
# Set up the drawing window
screen = pygame.display.set_mode([SCREEN_HEIGHT, SCREEN_WIDTH],)
def main(logged_in = False):
    server = ServerCommunication("localhost", 9999)
    game = Game()
    game.create_room("Room 1")
    game.create_room("Room 2")
    game.create_room("Room 3")
    player = Player("",server)

    while True:

        input_box_for_name = InputBox(SCREEN_WIDTH // 2 - 70, (SCREEN_HEIGHT // 2) + 50, 140, 32, player.set_name)
        # Fill the background with white
        screen.fill((255, 255, 255))
        # Did the user click the window close button?
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                pygame.quit()
                exit()
            if not logged_in:
                input_box_for_name.handle_event(event)

        if not logged_in:
            draw_player_name_input(screen,input_box_for_name)
            if player.name != "":
                logged_in = True
        else:
            draw_room_list(screen,game)

        # Flip the display
        pygame.display.flip()


if __name__ == '__main__':
    pygame.init()
    main(logged_in)

