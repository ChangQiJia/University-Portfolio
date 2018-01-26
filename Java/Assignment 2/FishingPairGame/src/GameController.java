/*
 * CSCI 213 Assignment 2 
--------------------------
 * File name: GameController.java
 * Author : Chang Qi Jia 
 * Student Number : 5280618 09
 * Description : Main Code for the Game : "Controller"
 */

import java.util.*; 
import java.io.*;

public class GameController {
    
    private ArrayList <GamePlayer> players;
    public static GameView newTable;
    private String username; 
    private int win; 
    
    
    GameController (GameView newTable, ArrayList <GamePlayer> players, String username)
    {
        this.players = players; 
        this.newTable = newTable; 
        this.username = username; 
    }
    
    public void StartGame ()
    {        
        int firstCard, secondCard; 
        boolean match = false; 
        boolean valid = false; 
        char nextMove; 
        char quit = 'a';
       
        Scanner input = new Scanner (System.in);
        
        do
        {
            System.out.println ("Game Start!");
            newTable = new GameView (); 
            

            do
            {
                for (GamePlayer gamePlayers: players)
                {      
                  if (newTable.isFinished() == false)
                    {
                        newTable.printTable(); 
                        currentProgress(); 
                        System.out.println ("\n---------------------------------------------------------------------------");
                        System.out.print (gamePlayers.getName() + "'s Turn\n");
                        System.out.println ("---------------------------------------------------------------------------");

                        do
                        {
                          gamePlayers.printHint(); 
                          firstCard = gamePlayers.makeGuess();

                          if (newTable.validGuess(firstCard))
                           {
                               if (firstCard == 99)
                                    firstCard = gamePlayers.getHint();

                               newTable.showCards (firstCard);
                               valid = true; 
                           }

                        }while (valid == false); 

                        valid = false; 
                        System.out.println ("\n---------------------------------------------------------------------------");

                        do
                        {
                        secondCard = gamePlayers.makeGuess(); 

                            if (newTable.validGuess(secondCard) && secondCard != firstCard && secondCard != 99) 
                            {
                                newTable.showBothCards (firstCard, secondCard);
                                valid = true; 
                            }
                            else if (secondCard == firstCard)
                                System.out.println ("The card you chosen is the same as the previous, please choose a different card\n");

                        }while (valid == false); 

                        valid = false; 

                        System.out.println ("\n---------------------------------------------------------------------------");

                        match = newTable.matchCards (firstCard, secondCard);

                        if (match == true)
                        {
                            gamePlayers.addScore();

                            if (!newTable.isEmpty())
                            {
                                newTable.updateCards (firstCard);

                                if (!newTable.isEmpty())
                                    newTable.updateCards (secondCard);  

                                else
                                    newTable.removeCards(secondCard);
                            }

                            else
                            {
                                if (firstCard < secondCard)
                                {
                                    newTable.removeCards(firstCard);
                                    newTable.removeCards (secondCard-1);
                                }

                                else
                                {
                                    newTable.removeCards (firstCard);
                                    newTable.removeCards (secondCard);
                                }
                            }
                        }

                        else
                        {
                            nextMove = gamePlayers.nextMove(); 

                            if (nextMove == 'P' || nextMove == 'p')
                            {
                                if (!newTable.isEmpty())
                                {
                                    newTable.replaceCards (firstCard);
                                    System.out.println ("card " + firstCard + " placed back in the deck");

                                    if (!newTable.isEmpty())
                                    {
                                        newTable.replaceCards (secondCard);
                                        System.out.println ("card " +secondCard + " placed back in the deck");
                                    }

                                    else
                                        System.out.println ("Sorry there are no more cards in the deck");
                                }

                                else
                                    System.out.println ("Sorry there are no more cards in the deck");
                            }
                            else
                                System.out.println ("card " + firstCard + " and card " + secondCard + " turned back");

                            System.out.println ("---------------------------------------------------------------------------");
                        }
                    }  
                }
                
            }while (!newTable.isFinished());
            
            determineWinner(); 
            
            do
            {
                System.out.print("\nNext Game? [Y] to continue, [N] to quit: ");
        
                quit = input.next().charAt(0);
                
                if (quit == 'Y' || quit == 'y' || quit == 'n' || quit == 'N')
                    valid = true; 
                else
                    System.out.println ("Please enter either [Y] or [N]");
                
            }while (valid == false);
            
            valid = false; 
            
        }while (quit == 'Y' || quit == 'y');
    }

    
    public void determineWinner()
    {
        int highest = 0;
        String tempHighestPlayer = " ";
        ArrayList <String> highestPlayers= new ArrayList <String> (); 
        
        for (GamePlayer gamePlayers: players)
         {
             if (highest < gamePlayers.getScore())
             {
                 highest = gamePlayers.getScore(); 
             }
         }
         
        for (GamePlayer gamePlayers: players)
         {
             if (highest == gamePlayers.getScore())
             {
                 tempHighestPlayer = gamePlayers.getName();
                 highestPlayers.add(tempHighestPlayer);
             }
         }
        
        if (highestPlayers.size() == 1)
            System.out.println ("\n" + tempHighestPlayer + " wins!");
        
        else
        {
            System.out.print ("Players: ");
            
            for (String highestScorers: highestPlayers)
            {
                 System.out.print (highestScorers + " , ");
            }
            System.out.print ("ends in a draw!\n");
        }
         
         System.out.println ("The highest score is " + highest);
    }
    
    public void currentProgress()
    {
        System.out.println ("\n");
        
        int highest = 0;
        
        for (GamePlayer gamePlayers: players)
        {
            if (highest < gamePlayers.getScore())
                 {
                     highest = gamePlayers.getScore(); 
                 }
        }
        
        for (GamePlayer gamePlayers: players)
         {
            System.out.print (gamePlayers.getName() + " Matching Pair: " + gamePlayers.getScore());        
            System.out.println (" -------- "+ (highest - gamePlayers.getScore()) + " matches to catch up");
         }
         System.out.println ("No. of cards remaining in deck: " + newTable.showDeck());
    }
    
    public int checkWin () 
    {
        int highest = 0; 
        String tempHighestPlayer = " ";
        
        ArrayList <String> highestPlayers= new ArrayList <String> (); 
        
        for (GamePlayer gamePlayers: players)
         {
             if (highest < gamePlayers.getScore())
             {
                 highest = gamePlayers.getScore(); 
             }
         }
         
        for (GamePlayer gamePlayers: players)
         {
             if (highest == gamePlayers.getScore())
             {
                 tempHighestPlayer = gamePlayers.getName();
                 highestPlayers.add(tempHighestPlayer);
             }
         }
        
        if (highestPlayers.size() == 1)
            if (tempHighestPlayer.equals(username))
                win ++; 
        
        return win; 
    }
    
}
    
    
