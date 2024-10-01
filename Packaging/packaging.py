# Given a list of integers create sub-lists that use items from the list only once
# Where the sum of the members of the sublist is less than or equal to some threshold.


def sum_of_list(list):
    total = 0
    for item in list:
        total += item
    return total

def find_set_close_to_threshold(threshold, values):
    new_set = []
    for value in values:
        if value + sum_of_list(new_set) <= threshold:
            new_set.append(value)

    return new_set

def create_groups_of_size(size, values):
    values.sort(reverse=True) # reverse sort helps produce best results.
    results = []
    while len(values) > 0:
        found = find_set_close_to_threshold(threshold, values)
        for x in found:
            values.remove(x)

        results.append(found)

    return results


values = [3,1,4,5,6,7,8,8,9,10]
threshold = 15 # less than or equal
'''
[8,7] = 15
[10, 5] = 15
[6, 9] = 15
[3,4,8] = 15
[1] = 1
'''
print(values)
print(threshold)
results = create_groups_of_size(threshold, values)
print(results)