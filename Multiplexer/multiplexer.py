# A class representing a MUX (Multiplexer)
# https://en.wikipedia.org/wiki/Multiplexer

 
class Multiplexer:

    def __init__(self, input_names=['A', 'B', 'C', 'D']):
        self.__bit_size = (len(input_names)-1).bit_length()
        self.__mappings = {}

        for index, name in enumerate(input_names):
            self.__mappings.update( {name: self.__get_bit_tuple(index)})


    def __get_bit_tuple(self, num):
        binary_string = bin(num)[2:]  # Remove the '0b' prefix
        binary_string = binary_string.rjust(self.__bit_size,'0')
        return tuple(int(bit) for bit in binary_string)
 
 
    def get_selected(self, selectors):
        for output, bits in self.__mappings:
            if bits == selectors:
                return output
 
 
    def selectors_for(self, desired):
        return self.__mappings.get(desired)


    def __repr__(self):
        out_str = 'Multiplexer: {} by 1\n'.format(len(self.__mappings))
        out_str += '    OUT -> SELECTOR Bits\n'
        out_str += '    --------------------\n'
       
        for key, bits in self.__mappings.items():
             out_str += '    "{}" -> {}\n'.format(key, bits)

        return out_str




''' # Comment out this line to run Examples
##############################################################################################################
# Examples

four_by_one = Multiplexer() # default
eight_by_one = Multiplexer(['A','B','C','D','E','F','G','H'])
sixteen_by_one = Multiplexer(['A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P'])

print(four_by_one)
print(eight_by_one)
print(sixteen_by_one)
##############################################################################################################'''