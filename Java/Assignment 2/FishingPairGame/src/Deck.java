/*
 * CSCI 213 Assignment 2 
--------------------------
 * File name: Deck.java
 * Author : Chang Qi Jia 
 * Student Number : 5280618 09
 * Description : Deck Class
 */

import java.util.*;

public class Deck {
    
    private ArrayList<Cards> cardsDeck; 
    
    
    public Deck ()
    {
        cardsDeck = new ArrayList <Cards>();
        String temp; 
        
        for (int i = 0; i < 4; i++)
        {
            if (i == 0)
                temp = "Diamonds";
            else if (i == 1)
                temp = "Clubs";
            else if (i == 2)
            temp = "Hearts";
            else
                temp = "Spades";
            
            Cards card; 
            
            card = new Cards (temp, " Ace");
            
            cardsDeck.add (card);
            
            for (int j = 2 ; j < 11 ; j++)
            {
                card = new Cards (temp, (" " + j));
                cardsDeck.add (card);
            }
            
            card = new Cards (temp, " Jack");
            
            cardsDeck.add (card);
            
            card = new Cards (temp, " Queen");
            
            cardsDeck.add (card);
            
            card = new Cards (temp, " King");
            
            cardsDeck.add (card);
            
        }
    }
    
    public void addCards (Cards newCard)
    {
        cardsDeck.add (newCard);
    }
    
    public Cards dealCards()
    {
        return cardsDeck.remove (0);
    }
    
    public void shuffle ()
    {
        Random r = new Random (); 
        int tempNum;
        
        for (int i = 0; i < 52 ; i++)
        {
            Cards a; 
            Cards b; 
            tempNum = r.nextInt (52);
            
            a = cardsDeck.get (i);
            b = cardsDeck.get (tempNum);
            
            cardsDeck.set (i, b);
            cardsDeck.set (tempNum,a);
        }
    }
    
    public void showCards()
    {   
       for(Cards Cards: cardsDeck){
    	   System.out.println(Cards);
       }
    }
    
    public boolean isEmpty () 
    {
        return cardsDeck.isEmpty ();
    }
    
    public int size ()
    {
        return cardsDeck.size();
    }
    
    public static void main(String []args)
    {
        //test deck
        Deck deck = new Deck();
        deck.showCards();
        deck.shuffle();
        deck.showCards();
        
        System.out.println ("-----------"); 
        
    }
}
