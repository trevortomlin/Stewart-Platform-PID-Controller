import matplotlib.pyplot as plt
import math
import numpy as np

BASE_ANGLE_OFFSET = 21.801
PLATFORM_ANGLE_OFFSET = 5.161
BASE_ANGLES = [360 - BASE_ANGLE_OFFSET, BASE_ANGLE_OFFSET, 120 - BASE_ANGLE_OFFSET, 120 + BASE_ANGLE_OFFSET, 240 - BASE_ANGLE_OFFSET, 240 + BASE_ANGLE_OFFSET]
PLATFORM_ANGLES = [300 + PLATFORM_ANGLE_OFFSET, 60 - PLATFORM_ANGLE_OFFSET, 60 + PLATFORM_ANGLE_OFFSET, 180 - PLATFORM_ANGLE_OFFSET, 180 + PLATFORM_ANGLE_OFFSET, 300 - PLATFORM_ANGLE_OFFSET]
BASE_RADIUS = 94.24
PLATFORM_RADIUS = 77.815
SERVO_HEIGHT = 40.0
PLATFORM_HEIGHT = 228.6 - SERVO_HEIGHT
SERVO_HORN_LENGTH = 23
BETA = [math.pi / 2, -math.pi / 2, -5 * math.pi / 6, math.pi / 6, -math.pi / 6, 5 * math.pi / 6 ]
LEG_LENGTH = 200.1
w0 = [1650, 1650, 1625, 1625, 1650, 1575]

def main():

	fig = plt.figure()
	ax = plt.axes(projection ='3d')

	ax.set_ylim(-100, 100)
	ax.set_xlim(-100, 100)
	ax.set_zlim(0, 250)

	ax.set_xlabel("x axis")
	ax.set_ylabel("y axis")

	t = [0, 0, PLATFORM_HEIGHT]
	r = calc_r(0, 0, 0)

	b = calc_b()

	p, q, angles, a, pw, dl = go_to(t, r, b)

	print(f"Angles: {str(angles) : >49}")
	print(f"Lengths of Dl: {str([np.linalg.norm(x) for x in dl]) : >144}")
	print(f"Length between a[1] and a[0]: {np.linalg.norm(a[0] - a[1]) : >27}")
	print(f"Length between b[1] and b[0]: {np.linalg.norm(b[0] - b[1]) : >26}")
	print(f"Length between p[5] and p[0]: {np.linalg.norm(p[5] - p[0]) : >27}")
	print(f"Pulse Widths: {str(pw): >73}")

	draw_vectors(b, [0,0,0], ax, "blue")
	draw_vectors(np.dot(p, r), t, ax, "red")
	draw_vectors(q, [0,0,0], ax, "c")
	draw_vectors(a, [0,0,0], ax, "g")
	draw_vectors(dl, a, ax, "orange")

	plt.show()

def go_to(t, r, b):

	p = calc_p()
	q = calc_q(p, t, r)

	angles = calc_angle(b, q)
	a = calc_a(b, angles)

	pw = calc_w(angles)

	dl = q - a

	return p, q, angles, a, pw, dl


def calc_r(phi, psi, theta):

	r = np.zeros((3,3))

	r[0][0] = (math.cos(psi) * math.cos(theta));
	r[0][1] = ((-math.sin(psi) * math.cos(phi)) + (math.cos(psi) * math.sin(theta) * math.sin(phi)));
	r[0][2] = ((math.sin(psi) * math.sin(phi)) + (math.cos(psi) * math.sin(theta) * math.cos(phi)));
	r[1][0] = (math.sin(psi) * math.cos(theta));
	r[1][1] = ((math.cos(psi) * math.cos(phi)) + (math.sin(psi) * math.sin(theta) * math.sin(phi)));
	r[1][2] = ((-math.cos(psi) * math.sin(phi) + (math.sin(psi) * math.sin(theta) * math.cos(phi))));
	r[2][0] = (-math.sin(theta));
	r[2][1] = (math.cos(theta) * math.sin(phi));
	r[2][2] = (math.cos(theta) * math.cos(phi));

	return r

def calc_w(angles):

	w = []

	r = 400 / 45

	for index in range(len(angles)):

		#print(angles[index], w0[index])

		if index % 2 ==0:

			w.append(round(w0[index] + (angles[index] - 0) * r, 0))

		else:

			w.append(round(w0[index] - (angles[index] - 0) * r, 0))

	return w

def calc_angle(b, q):

	t = [0,0,0,0,0,0]

	for l in range(len(b)):

		minAng, maxAng = -45, 45

		theta = 0
		n = 0

		while(n < 20):

			a = calc_a(b, t)

			dl = q[l] - a[l]

			if(abs(LEG_LENGTH - np.linalg.norm(dl)) < 0.01):

				t[l] = theta
				break

			else:

				if (np.linalg.norm(dl) < LEG_LENGTH):

					maxAng = theta

				else:

					minAng = theta

				n += 1

				if minAng == 45 or maxAng == -45:

					t[l] = theta
					break

				theta = minAng + (maxAng - minAng) / 2
				t[l] = theta

	return t

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

		p = [math.cos(math.radians(angle)) * PLATFORM_RADIUS, math.sin(math.radians(angle)) * PLATFORM_RADIUS, 0]
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

def calc_a(b, angles):

	As = []

	for i in range(len(b)):

		ang = angles[i]

		x = SERVO_HORN_LENGTH * math.cos(math.radians(ang)) * math.cos(BETA[i]) + b[i][0]
		y = SERVO_HORN_LENGTH * math.cos(math.radians(ang)) * math.sin(BETA[i]) + b[i][1]
		z = SERVO_HORN_LENGTH * math.sin(math.radians(ang)) + b[i][2]

		As.append([x,y,z])

	return np.array(As)

if __name__ == "__main__":
	main()