/*
* CSCI213 Assignment 3
* --------------------------
* File name: Dealer.java
* Author: Chang Qi Jia
* Student Number: 5280618
* Description: (A brief description of this class)
*/

public class Dealer extends GamePlayer {

	private Deck deck;
	private BrainInterface brainInterface;

	public Dealer(BrainInterface brainInterface) {
		super("Dealer", "", 0);
		deck = new Deck();
		this.brainInterface =  brainInterface;
	}

	public void shuffleCards() {

		deck.shuffle();
	}

	public Card dealCard() {
		return deck.dealCard();
	}
	
	public int getNumberOfCardsInDeck(){
		return deck.getNumberOfCards();
	}


}
