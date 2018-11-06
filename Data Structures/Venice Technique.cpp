/*
We want a data structure capable of doing three main update-operations and some 
sort of query. The three modify operations are: add: Add an element to the set.
remove: Remove an element from the set. updateAll: This one normally changes in 
this case subtract X from ALL the elements. For this technique it is completely 
required that the update is done to ALL the values in the set equally.
And also for this problem in particular we may need one query:
getMin: Give me the smallest number in the set.
*/
// Interface of the Data Structure
struct VeniceSet {
	void add(int);
	void remove(int);
	void updateAll(int); 
	int getMin(); // custom for this problem
	int size();
};

/*
Imagine you have an empty land and the government can make queries of the following 
type: * Make a building with A floors. * Remove a building with B floors. * Remove 
C floors from all the buildings. (A lot of buildings can be vanished) * Which is the 
smallest standing building. (Obviously buildings which are already banished don't count)
The operations 1,2 and 4 seems very easy with a set, but the 3 is very cost effective 
probably O(N) so you might need a lot of workers. But what if instead of removing C
floors we just fill the streets with enough water (as in venice) to cover up the 
first C floors of all the buildings :O. Well that seems like cheating but at least 
those floor are now vanished :). So in order to do that we apart from the SET 
we can maintain a global variable which is the water level. so in fact if we
have an element and want to know the number of floors it has we can just do 
height - water_level and in fact after water level is for example 80, if we 
want to make a building of 3 floors we must make it of 83 floors so that it 
can touch the land.
*/
struct VeniceSet {
	multiset<int> S;
	int water_level = 0;
	void add(int v) {
		S.insert(v + water_level);
	}
	void remove(int v) {
		S.erase(S.find(v + water_level));
	}
	void updateAll(int v) {
		water_level += v;
	}
	int getMin() {
		return *S.begin() - water_level;
	}
	int size() {
		return S.size();
	}
};
VeniceSet mySet;
for (int i = 0; i < N; ++i) {
	mySet.add(V[i]);
	mySet.updateAll(T[i]); // decrease all by T[i]
	int total = T[i] * mySet.size(); // we subtracted T[i] from all elements
	
	// in fact some elements were already less than T[i]. So we probbaly are counting 
	// more than what we really subtracted. So we look for all those elements
	while (mySet.getMin() < 0) {
		// get the negative number which we really did not subtracted T[i]
		int toLow = mySet.getMin(); 
		
		// remove from total the amount we over counted
		total -= abs(toLow);
		
		// remove it from the set since I will never be able to substract from it again
		mySet.remove(toLow);
	}
	cout << total << endl;
}
cout << endl;