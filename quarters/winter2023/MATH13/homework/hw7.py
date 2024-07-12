A = {1,2,3,4}
B = {2,3}
C = {3,4}
D = {4,1}
sets = [A,B,C,D]
for i,s1 in enumerate(sets[:-1]):
    for j,s2 in enumerate(sets[i+1:]):
        print(f"Set{i+1} and Set{i+j+2} = {s1&s2}")
