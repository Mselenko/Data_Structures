
bool candidate(int array[], int& canDidate, int sz);
bool majorityElement(const int arr[], int& majority, int sz);


/**
 * This function tests the candidate to ensure it is indeed the majority element
 *
 * @param arr      - array of integers where the majority element is supposed to be found,
 * @param majority - reference to an integer that passes back the value of the majority element if one exists,
 * @param sz       - the size of the array
 *
 * @return boolean value - true if majority element is found, false otherwise
 */
bool majorityElement(const int arr[], int& majority, int sz)
{
	if (sz == 1) return arr[0];

	int* arr2 = new int[sz];

	for (int i = 0; i < sz; i++)
		arr2[i] = arr[i];

	// Candidate function finds a candidate value and returns true
	if (candidate(arr2, majority, sz))
	{
		int count = 0;

		for (int i = 0; i <= sz; i++)
		{
			if (arr[i] == majority)
				count++;
		}
	// Checks that the candidate value appears more than 50% in the array
		if (count * 2 > sz) {
			delete[] arr2;
			return true;
		}
	}

	delete[] arr2;
	return false;
}

/**
 * Recursive function that searches for a candidate
 *
 * @param array     - array that we will look for the majority element in,
 * @param candidate - reference to an integer that passes back the candidate for the majority element if one is found,
 * @param sz        - the size of the array
 *
 * @return boolean value - true if a candidate is found, false otherwise,
 *                                                 also passes back the candidate if it is found
 */
bool candidate(int array[], int& canDidate, int sz)
{
	if (sz % 2 != 0)
		canDidate = array[sz - 1];

    // Returns the last value from the array if the numbers are the same
	// If the numbers are different, returns candidate value
	if (sz <= 2)
		return array[0] == array[1] ? array[1] : canDidate;

	int count = 0;

	int* arrTemp = new int[sz / 2 + 1];

	// For each pair, if the numbers are the same, saves either of them into a new array for the next iteration
	// If the numbers are different, keep neither of them
	for (int j = 0; j < sz; j += 2)
	{
		if (j + 1 < sz && array[j] == array[j + 1])
			arrTemp[count++] = array[j];
	}

	bool result = candidate(arrTemp, canDidate, count);

	delete[] arrTemp;
	return result;
}
