/*
 * CSCI 213 Assignment 1 
--------------------------
 * File name: Assignment_1.java
 * Author : Chang Qi Jia 
 * Student Number : 5280618 09
 * Description :
 */



import java.util.*; 
import java.io.*; 
public class AdminModule {

   public static void main (String [] args) {
        int option;  
        boolean loggedIn = false;  
        
        do 
        {
            option = menu (); 
            if (option == 1)
                if (loggedIn == false)
                    loggedIn = Admin.Login(); 
                else
                    System.out.println ("You are already logged in\n");
            
            else if (option == 2)
                if (loggedIn == true)
                    PlayerCreation.createPlayer ();
                else 
                    {
                        System.out.println ("Sorry you are not logged in as the admin yet\n");
                        loggedIn = Admin.Login(); 
                    }
            
            else if (option == 3)
                if (loggedIn == true)
                    PlayerDelete.deletePlayer ();
                else 
                    {
                        System.out.println ("Sorry you are not logged in as the admin yet\n");
                        loggedIn = Admin.Login(); 
                    }  
            
            else if (option == 4)
                if (loggedIn == true)
                    PlayerChangePass.changePlayerPass ();
                else 
                    {
                         System.out.println ("Sorry you are not logged in as the admin yet\n");
                         loggedIn = Admin.Login(); 
                    }
            
            else if (option == 5)
                if (loggedIn == true)
                    DisplayInfo.lookPlayerInfo ();
                else 
                    {
                         System.out.println ("Sorry you are not logged in as the admin yet\n");
                         loggedIn = Admin.Login(); 
                    }
            
            else if (option == 6)
                if (loggedIn == true)
                    DisplayPlayerScore.playerScore ();
                else 
                    {
                         System.out.println ("Sorry you are not logged in as the admin yet\n");
                         loggedIn = Admin.Login(); 
                    }
            
            else if (option == 7)
                if (loggedIn == true)
                    Admin.changeAdminPass ();
                else 
                    {
                         System.out.println ("Sorry you are not logged in as the admin yet\n");
                         loggedIn = Admin.Login(); 
                    }
            
        }while (option != 8);
    }
    
    public static int menu () {
        
        Scanner input = new Scanner (System.in);
        int temp;
        boolean loggedIn = false;
        
        System.out.println ("This is the main menu, please enter option.");
        System.out.println ("1. Login\n2. Create a player\n3. Delete a player");
        System.out.println ("4. Reset player's password\n5. Display a player's detail\n6. Display all players scores");
        System.out.println ("7. Change admin password\n8. Logout");
        
        System.out.print ("Option: ");
        
        if (input.hasNextInt())
        {
            temp = input.nextInt(); 
            
            if (temp > 0 && temp < 9)
                return temp; 
            else 
            {
                System.out.println ("You have entered an invalid option please re-enter");
                temp = menu ();
                return temp;
            }
        }
        
        else 
        {
            System.out.println ("You have entered an invalid option please re-enter");
            temp = menu ();
            return temp; 
        }
    }
    
}
