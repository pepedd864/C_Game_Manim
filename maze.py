from manimlib import *


def create_block(type):
    square = Square(0.3)
    square.set_fill(BLUE if type == 0 else BLACK, opacity=0.7)
    square.set_color(BLUE if type == 0 else BLACK)
    # label = Text(str(type), font_size=18, font="思源黑体")
    # square.add(label)
    return square


def create_grid(grid):
    group = VGroup()
    for i in grid:
        inner = VGroup()
        for j in i:
            inner.add(create_block(j))
        inner.arrange(RIGHT, buff=0)
        group.add(inner)
    group.arrange(DOWN, buff=0)
    return group


width = 31
height = 21
map = [[0 for _ in range(width)] for _ in range(height)]  # 0表示未访问过，1表示访问过


def dig(self, x, y):
    # 使用2的原因是利用间隔来形成墙
    a = [[2, 0], [-2, 0], [0, 2], [0, -2]]  # 方向 右 左 下 上
    for i in range(4):
        j = random.randint(0, 3)
        if i != j:
            a[i], a[j] = a[j], a[i]
    map[x][y] = 1
    for i in range(4):
        # 判断是否越界 或者是否已经访问过
        if (
            x + a[i][0] < 0
            or x + a[i][0] >= height
            or y + a[i][1] < 0
            or y + a[i][1] >= width
            or map[x + a[i][0]][y + a[i][1]] == 1
        ):
            continue
        # 将两个格子之间的墙打通
        map[x + a[i][0] // 2][y + a[i][1] // 2] = 1
        dig(x + a[i][0], y + a[i][1])


class Maze(Scene):
    def construct(self):
        group = create_grid(map)
        self.play(Write(group))
        self.scene.remove(self.scene.mobjects[-1])
        # dig(self, 1, 1)
