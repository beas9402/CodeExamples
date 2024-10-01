

class Primes:
    def __init__(self):
        self._known = [2]
        self.find(limit=100)

    def find(self, limit):
        for candidate in range(self._known[-1], limit):
            is_prime = True
            for prime in self._known:
                fractional = int(candidate / prime)
                if fractional * prime == candidate:
                    is_prime = False
            if is_prime:
                self._known.append(candidate)

    def is_prime(self, x):
        if x > self._known[-1]:
            self.find(x)
        return x in self._known

    @property
    def known(self):
        return self._known


p = Primes()

print(17, 'isPrime', p.is_prime(17))
print(1500, 'isPrime', p.is_prime(1500))

print(p.known)