#include <Adafruit_NeoPixel.h>
#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include "RGB.h"
#include "Cards.h"
#include "random.h"

#define PIN 1

Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(8, 8, PIN,
  NEO_MATRIX_TOP     + NEO_MATRIX_LEFT +
  NEO_MATRIX_ROWS + NEO_MATRIX_PROGRESSIVE,
  NEO_GRB            + NEO_KHZ800);

Card deck[52];
int deckIndex;

void setup() {
  matrix.begin();
  matrix.setBrightness(5);
  matrix.setTextColor( matrix.Color(white.r, white.g, white.b) );
  matrix.setTextWrap(false);

  randomSeed(seedOut(31));

  newDeck();  
}

void newDeck() {
  int n = 0;
  for (int s=0; s < 4; s++) {
    for (int f=0; f < 13; f++) {
      Card card = { (Suit)s, CardFaces[f] };
      deck[n++] = card;
    }
  }
  shuffle();
  shuffle();
  deckIndex = 0;
}

void shuffle() {
  for (int ndx=0; ndx < 52; ndx++) {
    int pos = random(52);
    Card a = deck[pos];
    deck[pos] = deck[ndx];
    deck[ndx] = a;
  }
}

void loop() {
  if (deckIndex == 52) {
    newDeck();
  }
  drawCard(deck[deckIndex++]);
}

void drawCard(Card card) {
  Suit suit = card.suit;
  String face = card.face;
  String composite = face + SuitASCII[suit];
  RGB color = (suit == hearts || suit == diamonds) ? red : white;
  scrollText(composite, color);
}

void scrollText(String textToDisplay, RGB fgColor) {
  int x = matrix.width();
  int pixelsInText = textToDisplay.length() * 7;
  
  matrix.setCursor(x, 0);
  matrix.print(textToDisplay);
  matrix.show();
  
  while(x > (matrix.width() - pixelsInText)) {
    matrix.fillScreen(colorFromRGB(black));
    matrix.setTextColor(colorFromRGB(fgColor));
    matrix.setCursor(--x, 0);
    matrix.print(textToDisplay);
    matrix.show();
    delay(150);
  }
}

uint16_t colorFromRGB(RGB color) {
  return matrix.Color(color.r, color.g, color.b);
}

