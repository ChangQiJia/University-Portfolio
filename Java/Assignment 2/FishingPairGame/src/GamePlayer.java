/*
 * CSCI 213 Assignment 2 
--------------------------
 * File name: GamePlayer.java
 * Author : Chang Qi Jia 
 * Student Number : 5280618 09
 * Description : Player Controller
 */

import java.util.*;


public class GamePlayer implements PlayerInterface{
    
    private boolean isHuman = false;
    private int score; 
    private String playerName; 
    private int hint = 3; 
    
    GamePlayer (String username)
    {
        this.playerName = username; 
    }
    
    GamePlayer (boolean humanPlayer, String username)
    {
        this.isHuman = humanPlayer; 
        this.playerName = username; 
    }
    
    public char nextMove()
    {
        System.out.print ("Would you like to [T]urn back the cards or [P]lace the cards at the end of the deck? ");
        
        Scanner input = new Scanner (System.in); 
        
        char move; 
        
        move = input.next().charAt(0); 
        
        if (move == 'T' || move == 't' || move == 'P' || move == 'p')
            return move;
        else
        {
            System.out.println ("Sorry please enter a valid option");
            return nextMove (); 
        }
        
    }

    
    public boolean isHuman()
    {
        return isHuman;
    }
    
    public int getScore()
    {
        return score; 
    }
    
    public int makeGuess ()
    {
        System.out.print ("Which card would you like to guess?: ");
        
        Scanner input = new Scanner (System.in); 
        
        int index = 0; 
        
        if (input.hasNextInt())
            index = input.nextInt(); 
        else
            {
                System.out.println ("Sorry please enter an integer");
                return makeGuess (); 
            }
     
        return index; 
    }
    
    public String getName ()
    {
        return playerName;
    }
    
    public void addScore ()
    {
        score++;
    }
    
   public int getHint () 
   {
       hint--;
       
       int index = 0; 
       
       index = GameController.newTable.findMatch();
       System.out.println (" " + index);
       
       return index; 
   }
   
   public void printHint()
   {
       System.out.println ("Enter [99] for hint, you have " + hint + " more hints, only usable on 1st guess" );
   }
}

