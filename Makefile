
all:
	g++ fiddling.cpp -o fiddle

preprocessed:
	g++ -E fiddling.cpp -o preprocessed.out
