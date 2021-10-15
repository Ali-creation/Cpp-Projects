#include "ex1.h"

static int dot_helper(list_t v1, list_t v2, int result){
	if(list_isEmpty(v1) || list_isEmpty(v2))
		return result;
	int firstElt1 = list_first(v1);
	int firstElt2 = list_first(v2);
	int dotProduct = firstElt1 * firstElt2;
	result += dotProduct;
	return dot_helper(list_rest(v1), list_rest(v2), result);
}

int dot(list_t v1, list_t v2){
	// TODO: implement dot function
	int result = 0;
	return dot_helper(v1, v2, result);
}

static bool odd(int num){
	if(num%2 != 0)
		return true;
	return false;
}

list_t filter_odd(list_t list){
	// TODO: implement filter_odd function
	return filter(list, odd);
}

static list_t reverse_helper(list_t list, list_t reversed){
	if(list_isEmpty(list))
		return reversed;
	int firstElt = list_first(list);
	reversed = list_make(firstElt, reversed);
	return reverse_helper(list_rest(list), reversed);
}

static list_t reverse(list_t list){
	list_t reversed = list_make();
	return reverse_helper(list, reversed);
}

static list_t filter_helper(list_t list, bool (*fn)(int), list_t result){
	if(list_isEmpty(list))
		return result;
	int firstElt = list_first(list);
	if(fn(firstElt))
		result = list_make(firstElt, result);
	return filter_helper(list_rest(list), fn, result);
}

list_t filter(list_t list, bool (*fn)(int)){
	// TODO: implement filter function
	list_t result = list_make();
	result = filter_helper(list, fn, result);
	return reverse(result);
}


