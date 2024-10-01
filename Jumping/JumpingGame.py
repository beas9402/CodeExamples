# A jumping game
# The list of integers represents the maximum number of jumps allowed from that spot in the list
# once in the new spot you can jump UPTO whatever number of jumps is in that spot
# can you reach the last element in the array?
# example [2,1,0,5] -> from position 0 you are allowed UPTO 2 jumps
#                      jumping once lands you on the '1' which allows you to jump 1 to the '0' then you are stuck
#                      jumping twice lands you on the '0' so you are stuck
#                      since there are no other options you CANNOT reach the last element '5'
#
# example [2,0,1,5] -> from position 0 you are allowed UPTO 2 jumps
#                      jumping once lands you on the '0' so you are stuck
#                      jumping twice lands you on the '1' which allows you to jump 1 to the '5'
#                      congrats you made it to the last element

def can_reach_end(start, elements):
    # TODO check bounds
    jumps = elements[start]
    # print(jumps, start, elements)
    if jumps+start >= len(elements) -1:
        return True
    else:
        for x in range(1, jumps):
            if can_reach_end(start + x, elements):
                return True
        return False

print("A Jumping Game: Can you reach the end?")
nums = [2,3,1,1,4] # should be able to reach the end
print ()
print (nums)
print (can_reach_end(0, nums))

nums2 = [3,2,1,0,4] # should not be able to reach the end
print ()
print (nums2)
print (can_reach_end(0, nums2))

# can I reach the end if I concat the lists??
print ()
print (nums+nums2)
print ( can_reach_end(0, nums + nums2))

