# visual representation of recursions that solves the tower of hanoi using turtleeee
import turtle
from colorsys import hsv_to_rgb
from time import sleep

DISK_HEIGHT = 20 # height of each discs
disks = {'A': [], 'B': [], 'C': []} # disks currently present in each pegs
peg_positions = {'A': -350, 'B': -100, 'C': 150} # horizontal position of pegs

def toh(n, start, end, aux): # from start -> end with the help of aux peg
    if n == 0:
        return
    else:
        # move n-1 discs from start to aux peg
        toh(n-1, start, aux, end)

        # move the nth disk from start peg to end peg
        sleep(1) # to visualize what is happening on the screen lol!
        move_disk(n, start, end)
        print(f"Moved disk {n} from peg {start} to {end}")

        # move the n-1 discs from aux to end peg
        toh(n-1, aux, end, start)

def draw_peg(x, y, color, label):
    peg = turtle.Turtle()

    peg.color(color)
    peg.penup()
    peg.goto(x, y)
    peg.pendown()
    # base-box
    for _ in range(2):
        peg.forward(150)
        peg.right(90)
        peg.forward(50)
        peg.right(90)
    peg.penup()
    peg.forward(50)
    peg.right(90)
    peg.forward(35)
    peg.write(label, font=24)
    peg.right(180)
    peg.forward(35)
    peg.pendown()
    peg.forward(500)
    peg.right(90)
    peg.forward(50)
    peg.right(90)
    peg.forward(500)
    peg.left(90)
    peg.penup()
    peg.hideturtle()

def draw_pegs():
    draw_peg(peg_positions['A'], -200, 'blue', 'Peg A')
    draw_peg(peg_positions['B'], -200, 'red', 'Peg B')
    draw_peg(peg_positions['C'], -200, 'green', 'Peg C')

def draw_disk(peg, size):
    disk_width = (size * DISK_HEIGHT) + 50 # so that the smallest disk is at least thet width of center rod
    disk = turtle.Turtle()

    # position of disk on the corresponding peg
    # peg ko base ko size 150 xa, disk ko size (size * DISK_HEIGHT xa), now disk lai center ma lagna paryo
    x = (peg_positions[peg] + 75) - (disk_width / 2) # at the center of the peg
    y = calculate_disk_y_position(peg, size)

    disk.penup()
    disk.goto(x, y)

    # draw rectangle disks
    disk.pendown()
    #disk.color('black', '#FFFFFF') -> for filling the color white inside
    disk.color('black', get_unique_color(size))
    disk.begin_fill()
    for _ in range(2):
        disk.forward(disk_width)
        disk.left(90)
        disk.forward(DISK_HEIGHT)
        disk.left(90)
    disk.end_fill()

    disk.hideturtle()

    # disks[peg].append(disk)
    return disk

# calculate the Y position of a disk based on the no. of disks present on that peg
def calculate_disk_y_position(peg, size):
    # -199 offsets the position of turtle initial above the base of the box on the peg
    # then it goes up depending on the number of discs already present on that peg
    return -199 + (len(disks[peg]) * DISK_HEIGHT)

def initialize_disks_on_pegA(n):
    # n -> no. of disks in the TOH
    for i in range(n, 0, -1):
        disk = draw_disk('A', i)
        disks['A'].append(disk)

def move_disk(disk_size, start, end):
    # find the corresponding turtle objects for the disks on the start and end pegs
    start_disk = disks[start].pop()

    start_disk.clear()

    # update the position of disc in dictionary and move the disk to new position
    new_disk = draw_disk(end, disk_size)
    disks[end].append(new_disk)
    turtle.update()

# get unique color for each disks
def get_unique_color(size):
    hue = (size * 30) % 360 # adjusting the multiplier for unique color variations
    rgb = hsv_to_rgb(hue / 360, 0.8, 0.8)

    # convert rgb to turtle color string
    turtle_color = "#{:02x}{:02x}{:02x}".format(
        int(rgb[0] * 255),
        int(rgb[1] * 255),
        int(rgb[2] * 255)
    )
    return turtle_color

def main():
    n = int(input("Enter no. of disks: "))
    while (n <= 0):
        n = int(input("Enter valid positive number: "))
    
    screen = turtle.Screen()
    screen.bgcolor('black')

    # draw the initial rods
    draw_pegs()

    # draw the initial disks at source
    initialize_disks_on_pegA(n)
    
    toh(n, 'A', 'C', 'B')
    
    turtle.tracer(1, 0) # ensures the screen updates after each movement
    turtle.done()

main()
