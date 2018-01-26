/*
 * CSCI 213 Assignment 2 
--------------------------
 * File name: ComputerPlayer.java
 * Author : Chang Qi Jia 
 * Student Number : 5280618 09
 * Description : Brain of Computer
 */


import java.util.*;

public class ComputerPlayer extends GamePlayer{
    
    private int difficulty; 

    
    public ComputerPlayer(String username, int difficulty) {
		super(username);
                this.difficulty = difficulty; 
	}
    
    public char nextMove()
    {
        int options; 
        
        Random r = new Random (); 
        
        options = r.nextInt (2);
        
        if (options == 1)
        {
            System.out.println ("T");
            return 'T';
        }
        else
        {
            System.out.println ("P");
            return 'P';
        }      
    }
    
    public int makeGuess ()
    {
        System.out.print ("Which card would you like to guess?: ");
        
        int index = 0; 
        
        if (difficulty == 1)
            index = easyBrain(); 
        
        else
            index = hardBrain(); 
        
        return index; 
    }
    
    public int easyBrain () 
    {
        int index = 0; 
        
        Random r = new Random ();
        
        index = r.nextInt(GameController.newTable.showSize())+1; 
        
        System.out.println (index);
        
        return index; 
    }
    
    public int hardBrain () 
    {
        int index = 0; 
        String answer = " ";
        int option = 0; 
        
        Random r = new Random ();
        
        option = r.nextInt(2); 
        
        if (option == 1)
        {
            index = GameController.newTable.findMatch();
            System.out.println (index);
        }
        else
            index = easyBrain(); 
        
        return index; 
    }
}
