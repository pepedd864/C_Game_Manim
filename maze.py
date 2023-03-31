from turtle import update
from manimlib import *

# 渐变动画时长
fade_during = 0.15
width = 21
height = 15
clen = 0.45
# 起点
start = [1, 1]
# 终点
end = [height - 2, width - 2]
map = [[0 for _ in range(width)] for _ in range(height)]  # 0表示未访问过，1表示访问过


class Maze(Scene):
    def dig(self, group, x, y):
        # 使用2的原因是利用间隔来形成墙
        a = [[2, 0], [-2, 0], [0, 2], [0, -2]]  # 用于随机选择方向
        text = "自动生成迷宫" + "(" + str(x) + "," + str(y) + ")"  # 标题
        # 判断是否是起点
        if x == start[0] and y == start[1]:
            map[x][y] = 4
            self.update_grid(group, map, text)
        # 判断是否到达终点
        if x == end[0] and y == end[1]:
            map[x][y] = 3
            self.update_grid(group, map, text)
            return
        for i in range(4):
            j = random.randint(0, 3)
            if i != j:
                a[i], a[j] = a[j], a[i]
        map[x][y] = 2
        self.update_grid(group, map, text)
        for i in range(4):
            # 判断是否越界 或者是否已经访问过
            if (
                x + a[i][0] < 0
                or x + a[i][0] >= height
                or y + a[i][1] < 0
                or y + a[i][1] >= width
                or map[x + a[i][0]][y + a[i][1]] == 1
                or map[x + a[i][0]][y + a[i][1]] == 2
            ):
                continue
            # 将两个格子之间的墙打通
            map[x + a[i][0] // 2][y + a[i][1] // 2] = 2  # 作为标记，在update_grid 中会更新为1
            text = "自动生成迷宫" + "(" + str(x) + "," + str(y) + ")"
            self.update_grid(group, map, text)
            self.dig(group, x + a[i][0], y + a[i][1])

    def create_block(self, type, i, j, x=0, y=0, len=0.3):
        block = Square(len)
        self.update_block(block, type).move_to([x, y, 0])
        label = Text(str(i) + "," + str(j), font_size=12, font="思源黑体")
        if type == 0:
            block.add(label)
        return block

    def update_block(self, block, type):
        if type == 0:
            block.set_fill(BLUE, opacity=0.7).set_stroke(width=1).set_color(BLUE)
        elif type == 2:
            block.set_fill(YELLOW, opacity=0.7).set_stroke(width=0)
        elif type == 3:
            block.set_fill(RED, opacity=0.7).set_stroke(width=0)
        elif type == 4:
            block.set_fill(GREEN, opacity=0.7).set_stroke(width=0)
        return block

    def create_slider(self, x, y, z=0, len=0.3):
        slider = Square(len, fill_opacity=0.7, fill_color=RED, stroke_width=0)
        slider.move_to([x, y, z])
        return slider

    def update_slider(self, slider, x, y, z=0):
        return slider.animate.move_to([x, y, z])

    def create_grid(self, grid, title):
        group = VGroup()
        for i in range(len(grid)):
            inner = VGroup()
            for j in range(len(grid[i])):
                if i == start[0] and j == start[1]:
                    inner.add(self.create_block(4, i=i, j=j, len=clen))
                elif i == end[0] and j == end[1]:
                    inner.add(self.create_block(3, i=i, j=j, len=clen))
                else:
                    inner.add(self.create_block(0, i=i, j=j, len=clen))
            inner.arrange(RIGHT, buff=0)
            group.add(inner)
        group.arrange(DOWN, buff=0)
        title = Text(title, font_size=20, font="思源黑体")
        title.move_to([0, (height / 2 + 1) * clen, 0])
        group.add(title)
        return group

    def update_grid(self, group, grid, title):
        for i in range(len(grid)):
            for j in range(len(grid[i])):
                if grid[i][j] == 2 or grid[i][j] == 1:
                    tmp = self.create_block(
                        grid[i][j],
                        i=i,
                        j=j,
                        x=group[i][j].get_x(),
                        y=group[i][j].get_y(),
                        len=clen,
                    )
                    self.update_block(
                        tmp,
                        grid[i][j],
                    )
                    if grid[i][j] == 2:
                        self.add(tmp)
                        self.play(FadeIn(tmp), run_time=fade_during)
                        self.play(FadeOut(tmp), run_time=0)
                        self.play(FadeOut(group[i][j]), run_time=fade_during)
                        grid[i][j] = 1
        # 更新标题
        text = Text(title, font_size=18, font="思源黑体")
        text.move_to([group[-1].get_x(), group[-1].get_y(), 0])
        self.play(Transform(group[-1], text), run_time=fade_during)
        group[-1].become(text)
        return group

    def construct(self):
        self.camera.background_color = WHITE
        group = self.create_grid(map, "创建迷宫")
        self.play(Write(group))
        self.dig(group, 1, 1)
        # self.play(Write(self.create_block(1,1,1)))
        # self.play(ReplacementTransform(group, self.create_grid(map)))
        # self.wait(1)
        # slider = self.create_slider(group[1][1].get_x(), group[1][1].get_y())
        # self.play(Write(slider))


if __name__ == "__main__":
    print("生成视频...")
    os.system("manimgl maze.py -pl")
