/*
 * CSCI 213 Assignment 2 
--------------------------
 * File name: checkValidLogin.java
 * Author : Chang Qi Jia 
 * Student Number : 5280618 09
 * Description : Deals with the players.dat file 
 */
import java.util.*; 
import java.io.*;
import java.text.*; 

public class checkValidLogin {
    
    private static String [] playerName = new String [10]; 
    private static String [] playerPass = new String [10]; 
    private static String [] playerLastLogin = new String [10];
    private static int [] playerScore = new int [10];
    private static int counter = 0; 
    
    public static boolean Valid(String username, String password){ 
    
    String [] dummy = new String [10]; 
    boolean success = false;
    Scanner fileInput = null;
    String temp;
    counter = 0; 
        try {
           
                fileInput = new Scanner (new File ("players.dat")); 
            }
        
        catch (FileNotFoundException ex)
        {
              
                    System.out.print ("Error in locating file, please make sure the file <players.dat> is available\n");
                    System.exit (-1);
           
        }
              
        while (fileInput.hasNextLine())
        {
            temp = fileInput.nextLine ();
            
            dummy= temp.split ("\\|");
        
            playerName [counter] = dummy[0];
            playerPass [counter] = dummy[1];
            playerLastLogin [counter] = dummy [2];
            playerScore [counter] = Integer.parseInt(dummy[3]);
            
            counter++; 
        }
        
        for (int i = 0 ; i < counter ; i++)
        {
            if (username.equals (playerName[i]))
                success = password.equals (playerPass [i]);
        }
        
        fileInput.close(); 
        
        if (success == true)
        {
            welcomeMessage (username);
            updateDate(username); 
        }
        return success;
   }
   
   public static String getDate () 
   {
       String current = " ";
       Date date = new Date();
       DateFormat dateFormat = new SimpleDateFormat (" yyy-MM-dd ");
       
       current = dateFormat.format(date);
       
       return current; 
   }
   
   public static void updateDate (String username)
   {
       for (int i = 0 ; i < counter ; i++)
        {
            if (username.equals (playerName[i]))
                playerLastLogin[i] = getDate ();
        }
       
       try 
       {
           updateFile (); 
       }
        catch (IOException ex)
        {
            System.out.println ("Failed to update file");    
        }
       
    }
   
   public static void updateFile () throws IOException
   {
          
        FileWriter fileOutput = new FileWriter ("players.dat");
      
        for (int i = 0; i < counter ; i++ )
            { 
                fileOutput.write (playerName[i] + "|");
                fileOutput.write (playerPass[i] + "|");
                fileOutput.write (playerLastLogin[i] + "|");
                fileOutput.write (playerScore[i] + "|");
                fileOutput.write (System.getProperty ("line.separator"));
            }
        
        fileOutput.close(); 
   }
   
   public static void welcomeMessage(String username) 
   {
       int oldYear, oldMonth, oldDays;
       int newYear, newMonth, newDays; 
       int year, month, days;
       
       String temp; 
       String [] dummy = new String [10];
       String [] whiteSpace = new String [10];
       
       temp = getDate(); 
       
       whiteSpace = temp.split ("\\s+");    
       dummy = whiteSpace[1].split ("-");
       
      
       newDays = Integer.parseInt(dummy[2]); 
       newMonth = Integer.parseInt(dummy[1]);
       newYear = Integer.parseInt(dummy[0]);
       
       for (int i = 0 ; i < counter ; i++)
        {
            if (username.equals (playerName[i]))
                temp = playerLastLogin[i];
        }
       
       whiteSpace = temp.split ("\\s+");
       
       dummy = whiteSpace[1].split ("-");
       
       oldDays = Integer.parseInt(dummy[2]);
       oldMonth = Integer.parseInt(dummy[1]);
       oldYear = Integer.parseInt(dummy[0]);
       
       days = newDays - oldDays; 
       month = newMonth - oldMonth; 
       year = newYear - oldYear; 
       
       if (days < 0)
       {
           month --;
           days += 30;
       }
       
       if (month < 0)
       {
           year --;
           month += 12;
       }
       
       System.out.print ("Welcome back " + username + " we have missed you for ");
       
       if (year > 0)
        {
            System.out.print (year + " year ");
        }
       if (month > 0)
       {
           System.out.print (month + " month and ");
       }
       
        System.out.print (days + " days!\n");
   }
   
   public static void updateScore (String username, int timesWon) 
   {
       for (int i = 0 ; i < counter ; i++)
        {
            if (username.equals (playerName[i]))
                playerScore[i]+= timesWon;
        }
       
       try 
       {
           updateFile (); 
       }
        catch (IOException ex)
        {
            System.out.println ("Failed to update file");    
        }
   }
}
