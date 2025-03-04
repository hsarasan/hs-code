import unittest

def doesExist(nums,target):
    hash_set=set()
    for num in nums:
        if target-num in hash_set:
            return True
        hash_set.add(num)
    return False


# Test Case Class
class TestSolution(unittest.TestCase):
    def test_add_positive(self):
        self.assertEqual(doesExist([1,2,3,4],5),True)

    def test_add_negative(self):
        self.assertEqual(doesExist([1,2,3,4],9),False)

# Run the tests
if __name__ == '__main__':
    unittest.main()

    