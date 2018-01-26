/*
* CSCI213 Assignment 4
* --------------------------
* File name: Guess.java
* Author: Chang Qi Jia
* Student Number: 5280618
* Description: Object to store computer's guess
*/

import java.io.*; 
import java.util.*; 
import java.net.*; 
import javax.swing.*; 
import java.awt.event.*; 
import java.awt.*; 

public class Guess implements Serializable{
    
    private ArrayList <Card> cardsOnTable; 
    private Card card1; 
    private Card card2; 
    
    Guess (ArrayList <Card> cardsOnTable)
    {
        this.cardsOnTable = cardsOnTable; 
    }
    
    public ArrayList <Card> getCOT () 
    {
        return cardsOnTable; 
    }
    
    public Card getCard1 () 
    {
        return card1; 
    }
    
    public Card getCard2 () 
    {
        return card2; 
    }
    
    public void setCard1 (Card card)
    {
        this.card1 = card; 
    }
    
    public void setCard2 (Card card)
    {
        this.card2 = card; 
    }
    
}
