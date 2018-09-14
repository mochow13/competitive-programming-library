template<typename Out>
void split(const std::string &s, char delim, Out result) {
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        *(result++) = item;
    }
}

std::vector<std::string> split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    split(s, delim, std::back_inserter(elems));
    return elems;
}

// Continuous input
string line;
while( getline(cin,line) ) 
{
	stringstream ss( line ); // initialize kortesi
	int num; vector< int > v;
	while( ss >> num ) v.push_back( num ); // :P
	sort( v.begin(), v.end() );
	// print routine
}