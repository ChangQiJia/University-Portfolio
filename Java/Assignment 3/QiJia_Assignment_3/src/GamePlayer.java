/*
* CSCI213 Assignment 3
* --------------------------
* File name: GamePlayer.java
* Author: Chang Qi Jia
* Student Number: 5280618
* Description: Human Player
*/

import java.util.*;

public class GamePlayer extends Player implements GamePlayerInterface{

	private ArrayList<Card> cardsOnHand;
        private int score = 0 ; 
	
	public GamePlayer(String loginName, String hashedPassword, int points) {

		super(loginName, hashedPassword, points);
		cardsOnHand = new ArrayList<Card>();
	}
	
	
	public void addCards(Card card1, Card card2) {
		cardsOnHand.add(card1);
		cardsOnHand.add(card2);
		
	}

	public int getScore() {
		return score; 
	}

	public ArrayList<Card> getCardsOnHand() {
		return cardsOnHand;
	}
	
	public void clearCardsOnHand() {
		cardsOnHand.clear();
	}
	
	public int getFirstCardNumber(int maxNumberOfCard){
		
		return Keyboard.readInt("Enter Card 1:");
	}

	public int getSecondCardNumber(int maxNumberOfCard, int cardNumber1){
		return Keyboard.readInt("Enter Card 2:");
	}
	
	
	public static void main(String []args)
    {
    }
        
        public void addScore ()
        {
            score++; 
        }
        
        public void setScore (int s)
        {
            score = s; 
        }

}
