/*
 * CSCI 213 Assignment 2 
--------------------------
 * File name: PlayerInterface.java
 * Author : Chang Qi Jia 
 * Student Number : 5280618 09
 * Description : Interface for player
 */

import java.util.*; 

public interface PlayerInterface {
    
    public char nextMove();
    public boolean isHuman();
    public int getScore(); 
    public int makeGuess (); 
    public String getName (); 
    
    
}
