'''



'''

import turtle

# screen settings

WIDTH , HEIGHT = 800, 800
screen = turtle.Screen()
screen.setup(WIDTH,HEIGHT , startx= 50 , starty= 0)
screen.screensize(3*WIDTH,3*HEIGHT)
screen.bgcolor('black')
screen.delay(0)

#turtle settings

leo = turtle.Turtle()
leo.pensize(3)
leo.speed(0)
leo.color('green')
leo.setpos(-WIDTH//3,0)
leo.clear()
turtle.pencolor('white')

# l -system setting

gens = 10
axiom = 'FX'
# f,g draw a line segment
chr_1 , rule_1 = 'X', 'X+YF+'
chr_2 , rule_2 = 'Y', '-FX-Y'
step = 8
angle = 90

def apply_rules(axiom):
    res = ''
    for chr in axiom:
        if chr == chr_1:
            res += rule_1
        elif chr == chr_2:
            res += rule_2
        else :
            res += chr
    return res

for gen in range(gens):
    axiom = apply_rules(axiom)


for ch in axiom:
    if ch == chr_1 or ch == chr_2:
        leo.forward(step)
    elif ch == '+':
        leo.right(angle)
    elif ch == '-':
        leo.left(angle)




screen.exitonclick()