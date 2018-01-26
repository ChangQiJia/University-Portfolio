/*
* CSCI213 Assignment 4
* --------------------------
* File name: GameState.java
* Author: Chang Qi Jia
* Student Number: 5280618
* Description: Object to store the entire game
*/

import java.io.Serializable;
import java.util.*; 
import javax.swing.*; 
import java.awt.*; 
import java.io.*;
import java.awt.event.*; 
import javax.sound.sampled.*; 

 
public class GameState extends Thread implements Serializable{
    
    private Deck d; 
    private ArrayList <Card> cardsOnTable ; 
    private ArrayList <Players> players ; 
    private int noOfPlayer;
    private Thread t; 
    private int counter = 0; 
    
    private Admin a = new Admin(); 
    
   
    GameState (ArrayList <Players> p, int noOfPlayer)
    {
        players = p; 
        this.noOfPlayer = noOfPlayer; 
        a.getInfo(); 
        
        d = new Deck (); 
        cardsOnTable = new ArrayList <> (); 
        
        Card c;
        d.shuffle(); 
            
        for (int i = 0; i < 5 ; i++)
            {
                c = d.dealCard(); 
                addCard (c);
            }
    }
    
    public void run () 
    {        
    }
    
    public void addCard (Card c)
    {
        cardsOnTable.add (c); 
    }
    
    public Deck getDeck ()
    {
        return d; 
    }
    
    public ArrayList <Card> getCOT ()
    {
        return cardsOnTable; 
    }
    
    public int getNoPlayer ()
    {
        return noOfPlayer; 
    }
    
    public ArrayList <Players> getPlayers ()
    {
        return players; 
    }
    
    public void setWinner (Winner w)
    {
        String winnerName = w.getName(); 
        counter++; 
        
        if (counter == 1)
            a.updateScore (winnerName); 
    }
    
    
}
    
