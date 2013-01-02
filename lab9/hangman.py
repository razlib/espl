from random import choice

wordsList = ["hello","tolpin"]

def myPrint(word, lettersFound):
  s = ""
  for ch in word:
    if (ch in lettersFound):
      s+= ch
    else:
      s+= "_"
    s+= " "
  print s
  
 

def startNewGame():

  numberOfGuesses = 0
  maxGuesses = 5
  lettersFound = []
  lettersGuessed = []
  winFlag = False
  word = choice(wordsList)
  while 1:
    myPrint(word, lettersFound)
    print "Guesses left:", numberOfGuesses
    print "Letters Guessed:", list(set(lettersGuessed))
    letter = raw_input("guess a letter...")
    if letter not in lettersGuessed:
      lettersGuessed.append(letter)
      if letter not in word:
	numberOfGuesses += 1
      if letter in word:
	lettersFound.append(letter)
    
    if len(set(lettersFound)) == len(set(word)):
	winFlag = True
	break
    elif (numberOfGuesses > maxGuesses):
	break
    
  if (winFlag):
    print "You Win!"
  else:
    print "Game Over... the word was " + word
  c = raw_input("Another game...? (y/n)")
  if c == "y":
    return True
  else:
    return False
  

    
while 1:
  res = startNewGame()
  if res == False:
    break;



