Weerwolven

1. Commands send by host
  a. Init (dit geeft de speler zijn spelers id en zijn rol door, de naam word took meegegeven zodat het zeker bij de juiste speler aankomt)
	bevat: naam, id, role
  b. Weerwolf (dit roept de werewolf op)
	bevat geen data
  c. Heks (dit roept de heks op)
	bevat geen data
  d. Wakker (dit zorgt ervoor dat iedereen wakker wordt, dit stuurd ook door wie er die nacht vermoord is)
	bevat: murder, murder2
  e. Cupido (dit roept cupido op)
	bevat geen data
  f. Koppel (dit zorgt ervoor dat elke client weet wie er een Koppel is, de spelers kunnen dit niet zien)
	bevat: Koppel, koppel2
  g. Restart (dit stuurt naar elke client de vraag of ze het spel willen herstarten)
	bevat geen data
  h. Restart! (dit stuurt de uitkomst van de stemming door)
	Bevat: uitkomst stemmen voor te restarten
  i. Offline (dit zorgt ervoor dat iedere speler weet dat iemand geleaved is end at het spel herstart word)
	Bevat: speler die is geleaved
  j. endGame (dit is om te laten weten dat het spel afgelopen is)
	bevat geen data

2. Commands send by client
  a. Init (dit stuurt de naam van de speler door)
	bevat: naam
  b. Koppel	(hier stuurt cupido de spelers door die hij wilt koppelen)
	bevat: koppel1, koppel2
  c. murderdByWeerwolf (hier stuurt de werewolf door wie hij wilt vermoorden)
	bevat: spelernummer
  d. murderdByHeks (de heks stuurt hier door wie ze wilt vermoorden)
	bevat: spelersnummer
  e. heal (de heks stuurt door dat ze de vermoorde speler terug tot levend wilt wekken)
	bevat geen data
  f. niks (hier stuurt de heks door dat ze niks wilt doen)
	bevat geen data
  g. vote (hier stuurt de speler door wie hij/zij dekt wie de werewolf is)
	bevat: spelernummer
  h. restart (hier vraagt een speler om het spelt te herstarten)
  i. restartVote (hier stuurt elke speler wijn stem door voor het herstarten van het spel)
	bevat: vote
  j. control (dit stuurt om de minuut zijn id door voor het controleren of hij/zij nog online is)
	bevat: id


