def maximum(xs):
	x = xs[0]
	if x > maximum(xs[1::]):
		return x
	else:
		return maximum(xs[1::])


maximum([1,2,3,7,6,49,123])

input()
