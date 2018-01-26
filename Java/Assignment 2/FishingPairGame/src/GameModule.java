/*
 * CSCI 213 Assignment 2 
--------------------------
 * File name: GameModule.java
 * Author : Chang Qi Jia 
 * Student Number : 5280618 09
 * Description : Main Code for the Game : "Model"
 */

import java.util.*; 
import java.io.*;

public class GameModule {
    
    private ArrayList <GamePlayer> players;
    private String username = " ";
    private GameView newTable; 
    
    GameModule (String username, int noOfPlayers, int difficulty) 
    {
        players = new ArrayList <GamePlayer> (); 
        this.username = username; 
               
        GamePlayer humanPlayer = new GamePlayer (true, username);      
        players.add (humanPlayer);

        for (int i = 0; i < noOfPlayers; i++)
        {
           GamePlayer temp = new ComputerPlayer ("ComputerPlayer " + (i+1), difficulty);
           players.add (temp);
        }    
    }
    
    public int run () 
    {
        GameController newGame = new GameController (newTable, players, username );
        newGame.StartGame(); 
        
        return newGame.checkWin(); 
        
    }
    
}
