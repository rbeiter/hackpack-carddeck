enum Suit {
  hearts=0,
  diamonds=1,
  clubs=2,
  spades=3
};

String SuitASCII[4] = {"\03", "\04", "\05", "\06"};
String CardFaces[13] = {"A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};

struct Card {
  Suit suit;
  String face;
};
