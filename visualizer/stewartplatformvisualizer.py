import matplotlib.pyplot as plt
import math
import numpy as np

BASE_ANGLE_OFFSET = 26.6
PLATFORM_ANGLE_OFFSET = 3.7
BASE_ANGLES = [360 - BASE_ANGLE_OFFSET, BASE_ANGLE_OFFSET, 120 - BASE_ANGLE_OFFSET, 120 + BASE_ANGLE_OFFSET, 240 - BASE_ANGLE_OFFSET, 240 + BASE_ANGLE_OFFSET]
PLATFORM_ANGLES = [300 + PLATFORM_ANGLE_OFFSET, 60 - PLATFORM_ANGLE_OFFSET, 60 + PLATFORM_ANGLE_OFFSET, 180 - PLATFORM_ANGLE_OFFSET, 180 + PLATFORM_ANGLE_OFFSET, 300 - PLATFORM_ANGLE_OFFSET]
BASE_RADIUS = 78.0
SERVO_HEIGHT = 40.0
PLATFORM_HEIGHT = 228.0 - SERVO_HEIGHT
SERVO_HORN_LENGTH = 23.5
BETA = [math.pi / 2, -math.pi / 2, -5 * math.pi / 6, math.pi / 6, -math.pi / 6, 5 * math.pi / 6 ]
LEG_LENGTH = 205.0

def main():

	fig = plt.figure()
	ax = plt.axes(projection ='3d')

	ax.set_ylim(-90, 90)
	ax.set_xlim(-90, 90)
	ax.set_zlim(0, 200)

	ax.set_xlabel("x axis")
	ax.set_ylabel("y axis")

	t = [0, 0, PLATFORM_HEIGHT]
	r = np.eye(3)

	b = calc_b()
	p = calc_p()
	q = calc_q(p, t, r)
	l = calc_l(q, b)
	a = calc_a(b, 0)

	dl = q - a

	print("Length of Dl[0]: 			  ", np.linalg.norm(dl[0]))
	print("Length of l[0]: 			  ", np.linalg.norm(l[0]))
	print("Length between a[1] and a[0]: ", np.linalg.norm(a[0] - a[1]))
	print("Length between b[1] and b[0]: ", np.linalg.norm(b[0] - b[1]))
	print("Length between p[5] and p[0]: ", np.linalg.norm(p[5] - p[0]))

	draw_vectors(b, [0,0,0], ax, "blue")
	draw_vectors(p, t, ax, "red")
	draw_vectors(q, [0,0,0], ax, "c")
	#draw_vectors(l, [0,0,0], ax, "m")
	draw_vectors(a, [0,0,0], ax, "g")
	draw_vectors(dl, a, ax, "orange")

	plt.show()

def draw_vectors(vectors, start, ax, col):

	if len(start) == 3:

		for vector in vectors:

			ax.quiver(start[0], start[1], start[2], vector[0], vector[1], vector[2], color=col)

	elif len(start) == 6:

		for index in range(len(vectors)):

			ax.quiver(start[index][0], start[index][1], start[index][2], vectors[index][0], vectors[index][1], vectors[index][2], color=col)

def calc_b():

	bs = []

	for angle in BASE_ANGLES:

		b = (math.cos(math.radians(angle)) * BASE_RADIUS, math.sin(math.radians(angle)) * BASE_RADIUS, 0)
		bs.append(b)

	return np.array(bs)

def calc_p():

	ps = []
	
	for angle in PLATFORM_ANGLES:

		p = [math.cos(math.radians(angle)) * BASE_RADIUS, math.sin(math.radians(angle)) * BASE_RADIUS, 0]

		ps.append(p)

	return np.array(ps)

def calc_q(p, t, r):
	qs = []

	for index in range(len(p)):

		q = t + np.dot(p[index], r)

		qs.append(q)

	return np.array(qs)	

def calc_l(q, b):

	ls = []

	for index in range(len(b)):

		l = q[index] - b[index]

		ls.append(l)

	return np.array(ls)	

def calc_a(b, ang):

	As = []

	for i in range(len(b)):

		x = SERVO_HORN_LENGTH * math.cos(math.radians(ang)) * math.cos(BETA[i]) + b[i][0]
		y = SERVO_HORN_LENGTH * math.cos(math.radians(ang)) * math.sin(BETA[i]) + b[i][1]
		z = SERVO_HORN_LENGTH * math.sin(math.radians(ang)) + b[i][2]

		As.append([x,y,z])

	return np.array(As)

if __name__ == "__main__":
	main()