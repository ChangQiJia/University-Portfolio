/*
* CSCI213 Assignment 3
* --------------------------
* File name: GamePlayerInterface.java
* Author: Chang Qi Jia
* Student Number: 5280618
* Description: Player Interface for human and computer to implement
*/

import java.util.ArrayList;
import java.io.*;

public interface GamePlayerInterface extends Serializable{
	
	public int getFirstCardNumber(int maxNumberOfCard);
	public int getSecondCardNumber(int maxNumberOfCard, int cardNumber1);
	public String getLoginName();
	public void addCards(Card card1, Card card2);
	public int getScore();
        public void addScore(); 
        public void setScore (int s);
	
}
