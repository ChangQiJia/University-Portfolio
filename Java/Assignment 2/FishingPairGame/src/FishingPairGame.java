/*
 * CSCI 213 Assignment 2 
--------------------------
 * File name: FishingPairGame.java
 * Author : Chang Qi Jia 
 * Student Number : 5280618 09
 * Description : Main Function
 */

import java.util.*; 
import java.io.*; 

public class FishingPairGame {
    
    private static boolean loggedIn; 
    private static boolean cont = true;
    private static char temp; 
    private static boolean validNo; 
    private static int difficulty; 
    private static boolean valid = false;
    private static int attempts = 0; 
    
    public static void main (String args [])
    {
        int noOfPlayers = 0;
        
        System.out.println ("FISHING PAIR GAME LOGIN");
        System.out.println ("---------------------------------------------------------------------------");
        Scanner input = new Scanner (System.in);
        String username, password, hashedPassword; 
        
       do
        {
        System.out.println ("You have "+ (3 - attempts) +" attempts left to log in");
        attempts++;
        System.out.print ("Enter Login Name: ");
        username = input.nextLine ();
        
        System.out.print ("Enter Password: ");
        password = input.nextLine ();
        
        hashedPassword = Utility.getHash (password);
        
        loggedIn = checkValidLogin.Valid (username, hashedPassword);
        
        if (loggedIn == false)
        {
           do
            {
                System.out.print ("Sorry you have keyed in an invalid username/password, [Y] if you would like to try again, [N] to quit : ");
                temp = input.next().charAt(0); 
                
                if (temp == 'Y' || temp == 'y' || temp == 'n' || temp == 'N')
                    valid = true; 
                else
                    System.out.println ("Please enter either [Y] or [N]");
                
            }while (valid == false);
             
            if ((temp == 'y' || temp == 'Y' )&& attempts < 3)
            {
                cont = true;
                input.nextLine(); 
            }
            else
                cont = false; 
        }
        
        else
            cont = false; 
        
        }while (cont == true); 
       
        if (loggedIn == true)
        {
            do
            {
                System.out.print ("How Many Players Would you like? (1 - 4): ");
                               
                if (input.hasNextInt())
                {
                    noOfPlayers = input.nextInt();

                    if (noOfPlayers > 0 && noOfPlayers < 5)
                        validNo = true; 
                    else
                        System.out.println ("Sorry please enter an integer from 1 to 4 "); 
                }
                
                else
                {
                    System.out.println ("Sorry please enter an integer");
                    input.nextLine(); 
                } 
            
            }while (validNo == false);
            
            validNo = false;     
            do
            {
                System.out.print ("Which difficulty would you like to play? 1 for easy or 2 for hard? ");
                
               
                if (input.hasNextInt())
                {
                    difficulty = input.nextInt();

                    if (difficulty == 1 || difficulty == 2)
                        validNo = true; 
                    else
                        System.out.println ("Sorry please enter an integer either 1 or 2"); 
                } 

                else
                {
                    System.out.println ("Sorry please enter an integer"); 
                    input.nextLine(); 
                } 
            
            }while (validNo == false);
            
            GameModule newGame = new GameModule (username, noOfPlayers, difficulty);
            
            int timesWon = newGame.run(); 
            
            if (timesWon > 0)
                checkValidLogin.updateScore (username, timesWon) ;
        }
        
        }
    }

