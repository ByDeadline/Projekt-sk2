import pygame



SCREEN_WIDTH = 1000
SCREEN_HEIGHT = 1000
COLOR_LIGHT_BLUE = (0, 0, 255)
COLOR_DARK_BLUE = (0, 0, 128)
COLOR_GREY = (105, 105, 105)
logged_in = False
class Room():
    def __init__(self, name, players):
        self.name = name
        self.players = players
        self.player_count = len(players)
        self.started = False
    def add_player(self,player):
        self.players.append(player)
        self.player_count += 1
    def remove_player(self,player):
        self.players.remove(player)
        self.player_count -= 1
    def start_game(self):
        self.started = True
class Player():
    def __init__(self, name, room = None):
        self.name = name
        self.room = room
    def join_room(self, room):
        if room.started:
            return False
        if room.player_count >= 4:
            return False
        self.room = room
        room.add_player(self.name)
        return True

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
    def __init__(self, x, y, w, h, text=''):
        self.rect = pygame.Rect(x, y, w, h)
        self.color = COLOR_DARK_BLUE
        self.text = text
        self.txt_surface = pygame.font.Font(None, 32).render(text, True, self.color)
        self.active = False
        self.cursor = pygame.Rect(self.txt_surface.get_rect().bottomleft, (3, self.txt_surface.get_height()))
    def handle_event(self, event, player):
        if event.type == pygame.MOUSEBUTTONDOWN:
            # If the user clicked on the input_box rect.
            if self.rect.collidepoint(event.pos):
                self.active = True
                self.color = COLOR_LIGHT_BLUE
            else:
                self.active = False
                self.color = COLOR_DARK_BLUE
            # Change the current color of the input box.
            self.txt_surface = pygame.font.Font(None, 32).render(self.text, True, self.color)
        if event.type == pygame.KEYDOWN:
            if self.active:
                if event.key == pygame.K_RETURN:
                    print(self.text)
                    player.name = self.text
                    self.text = ''
                elif event.key == pygame.K_BACKSPACE:
                    self.text = self.text[:-1]
                else:
                    self.text += event.unicode
                # Re-render the text.
                self.txt_surface = pygame.font.Font(None, 32).render(self.text, True, self.color)
                # bounding rectangle of the text
                text_rect = self.txt_surface.get_rect(topleft=(self.rect.x + 5, self.rect.y + 10))

                # set cursor position
                self.cursor.midleft = text_rect.midright

    def update(self):
        # Resize the box if the text is too long.
        width = max(200, self.txt_surface.get_width()+10)
        self.rect.w = width
    def draw(self, screen):
        # Blit the text.
        screen.blit(self.txt_surface, (self.rect.x+5, self.rect.y+10))
        # Blit the rect.
        pygame.draw.rect(screen, self.color, self.rect, 2)
        # Blit the cursor
        if self.active:
            pygame.draw.rect(screen, self.color, self.cursor)

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

def draw_player_name_input(screen,player,input_box):
    font = pygame.font.Font('freesansbold.ttf', 32)
    text = font.render('Enter your name', True, COLOR_DARK_BLUE)
    textRect = text.get_rect()
    textRect.center = (SCREEN_WIDTH // 2, SCREEN_HEIGHT // 2)
    screen.blit(text, textRect)
    input_box.draw(screen)
    pygame.display.flip()




# Set up the drawing window
screen = pygame.display.set_mode([SCREEN_HEIGHT, SCREEN_WIDTH],)
def main(logged_in = False):

    game = Game()
    game.create_room("Room 1")
    game.create_room("Room 2")
    game.create_room("Room 3")
    player = Player("")

    while True:

        input_box_for_name = InputBox(SCREEN_WIDTH // 2 - 70, (SCREEN_HEIGHT // 2) + 50, 140, 32)
        # Fill the background with white
        screen.fill((255, 255, 255))
        # Did the user click the window close button?
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                pygame.quit()
                exit()
            if not logged_in:
                input_box_for_name.handle_event(event, player)

        if not logged_in:
            draw_player_name_input(screen,player,input_box_for_name)
            if player.name != "":
                logged_in = True
        else:
            draw_room_list(screen,game)

        # Flip the display
        pygame.display.flip()


if __name__ == '__main__':
    pygame.init()
    main(logged_in)

