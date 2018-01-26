/*
* CSCI213 Assignment 4
* --------------------------
* File name: Okay.java
* Author: Chang Qi Jia
* Student Number: 5280618
* Description: Object to communicate between client's okay button
*/

import java.io.*; 
import java.util.*; 
import java.net.*; 
import javax.swing.*; 
import java.awt.event.*; 
import java.awt.*; 

public class Okay implements Serializable{
    
    private String username; 
    private int noOfPlayers; 
    private int card1; 
    private int card2; 
    
    Okay (String username, int noOfPlayers) 
    {
        this.username = username; 
        this.noOfPlayers = noOfPlayers; 
    }
    
    Okay ()
    {
        username = "Done";
        noOfPlayers = 1; 
    }
    
    Okay (int card1, int card2)
    {
        username = "Card";
        noOfPlayers = 0; 
        this.card1 = card1; 
        this.card2 = card2; 
    }
    
    public String getName () 
    {
        return username;
    }
    
    public int getSize () 
    {
        return noOfPlayers; 
    }
    
    public int getCard1 () 
    {
        return card1; 
    }
    
    public int getCard2 () 
    {
        return card2; 
    }
}
