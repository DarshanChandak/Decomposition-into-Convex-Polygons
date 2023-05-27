import turtle
import time


def draw(file_name, color, show_number, factor, shift_x, shift_y):
    with open(file_name) as file:
        list = [tuple(float(s) for s in line.strip().split()) for line in file]
    turtle.speed(2)
    k = -1
    flag = False
    list_final = []
    col = 1
    screen = turtle.Screen()
    screen.colormode(255)
    index = 1
    sum_x = 0
    sum_y = 0
    count = 0
    for element in list:
        if not flag:
            k = element[0]
            count = k-1
            flag = True
            list_final = []
        else:
            list_final.append((element[0], element[1]))
            if k != 1:
                sum_x = sum_x+element[0]
                sum_y = sum_y+element[1]

            k = k-1
            if k == 0:
                print(list_final)
                turtle.color('black', color)
                turtle.begin_fill()
                j = 0
                turtle.penup()
                turtle.goto(
                    (shift_x+list_final[0][0])/factor, (shift_y+list_final[0][1])/factor)
                turtle.pendown()

                list_final.append(list_final[0])
                for i in range(0, len(list_final)):
                    turtle.goto(
                        (shift_x+list_final[j][0])/factor, (shift_y+list_final[j][1])/factor)
                    j = j + 1
                turtle.end_fill()
                if show_number:
                    turtle.penup()

                    turtle.goto((shift_x+sum_x/count)/factor,
                                (shift_y+sum_y/count)/factor)
                    sum_x = 0
                    sum_y = 0
                    turtle.pendown()

                    turtle.write(str(index), align="center",
                                 font=("Cooper Black", 10, "italic"))
                    index = index+1
                flag = False
        print(list)


with open("input.txt") as file:
    list = [tuple(float(s) for s in line.strip().split()) for line in file]
sum_x = 0
sum_y = 0
for i in range(1, len(list)):
    sum_x = sum_x+list[i][0]
    sum_y = sum_y+list[i][1]
sum_x = sum_x/list[0][0]
sum_y = sum_y/list[0][0]
draw("input.txt", "white", False, 1, -1*sum_x, -1*sum_y)
draw("output.txt", "cyan", True, 1, -1*sum_x, -1*sum_y)
time.sleep(1000)
