/*
* CSCI213 Assignment 4
* --------------------------
* File name: Admin.java
* Author: Chang Qi Jia
* Student Number: 5280618
* Description: In Charge of dealing with the players.dat file
*/

import java.util.*;
import java.io.*; 
import java.text.*; 

public class Admin implements Serializable{
    
    private static String [] playerName = new String [10]; 
    private static String [] playerPass = new String [10]; 
    private static String [] playerLastLogin = new String [10];
    private static int [] playerScore = new int [10];
    private static int counter = 0; 
    
    public boolean checkLogin (String username, String password) 
    {
        String [] dummy = new String [10]; 
        boolean success = false;
        Scanner fileInput = null;
        String temp;
        counter = 0; 
        password = Utility.getHash (password); 
        
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
            {   
                success = password.equals (playerPass [i]);
            }
                
        }
        
        fileInput.close(); 
      
        return success;
   }
    
    public void getInfo()
    {
        String [] dummy = new String [10];
        
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
        
        fileInput.close(); 
    }
    
    public String getDate () 
   {
       String current = " ";
       Date date = new Date();
       DateFormat dateFormat = new SimpleDateFormat (" yyy-MM-dd ");
       
       current = dateFormat.format(date);
       
       return current; 
   }
    
    public String getOldDate (String username) 
   {
       String old = " ";
       
       for (int i = 0 ; i < counter ; i++)
        {
            if (username.equals (playerName[i]))
            {
                old = playerLastLogin[i];
            }
        }
        
       updateDate(username); 
       return old; 
   }
    
    public void updateDate (String username)
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
   
   public void updateFile () throws IOException
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
   
   public void updateScore (String username) 
   {
       for (int i = 0 ; i < counter ; i++)
        {
            if (username.equals (playerName[i]))
                playerScore[i]++;
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
   
   public String getUserPass (String username)
   {
        for (int i = 0; i < counter ; i++ )
            { 
                if (username.equals(playerName[i]))
                    return playerPass[i];
            }
        return null ; 
   }
   
   public int getUserScore (String username)
   {
        for (int i = 0; i < counter ; i++ )
            { 
                if (username.equals(playerName[i]))
                    return playerScore[i];
            }
        return 0; 
   }
}
