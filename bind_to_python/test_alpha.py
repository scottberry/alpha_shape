import alpha_shape

if __name__ == '__main__':
    with open('bunny_1000') as f:
        my_list = [tuple(map(float, i.split(' '))) for i in f]

    out = alpha_shape.filter_vertices(my_list, 0.1)
    print len(my_list), len(out)
    print out
