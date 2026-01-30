import MTools as mt
x = mt.create_matrix(2,3)
data = [10, 5, 6, 7, 7, 8]
x.set_data(data)
y = x * x
y.print()