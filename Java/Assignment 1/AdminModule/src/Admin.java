


import java.io.*;
import java.util.*;


public class Admin {
     public static boolean Login () 
    {
        System.out.println ("\nOption 1: Admin Login\n");
        String password, hashedPassword, correctPass; 
        correctPass = " ";
        boolean loggedIn = false; 
       
        try {
           correctPass = fileInput ("admin.dat");
        }
        
        catch (FileNotFoundException ex)
        {
              try 
                {
                    adminPasswordOutput ("asd");        //Set default password as 123456 if there is no admin.dat file
                    System.out.println ("Created new admin.dat file default password is 123456");
                    return Login(); 
                }
        
             catch (IOException error)
                {
                    System.out.print ("Error in creating file");
                } 
             
        }
     
        Scanner input = new Scanner (System.in);
        
        System.out.print ("Please enter administrator password : ");
        password = input.nextLine ();
        hashedPassword = Utility.getHash(password);
        
        if (correctPass.equals (hashedPassword))
        {
            System.out.println ("Successful Login!\n");
            loggedIn = true; 
        }
        
        else
        {
             System.out.println ("Failed to login, please try again\n");
           
        }
     
        return loggedIn; 
    }
    
    public static void changeAdminPass (){
        System.out.println ("\nOption 7: Changing Admin Password\n");
        
        String newPass; 
        Scanner input = new Scanner (System.in);
        
        boolean valid = false; 
        boolean changed = false; 
        
       do
       {
           System.out.print ("Please enter new password: ");
            newPass = input.nextLine (); 
            System.out.println ("");

            try 
                    {
                        changed = samePassword (newPass, "admin.dat");
                        
                        if (changed == true)
                        {
                            adminPasswordOutput (newPass);
                            valid = true; 
                            System.out.println ("Password has been succesfully changed.");
                        }
                        
                        else
                        {
                            System.out.println ("The password you have keyed in is the same as previous. Please try again");
                        }
                    }

                 catch (IOException error)
                    {
                        System.out.print ("Error in changing password, please ensure that there is no folder or file named admin.dat\n");
                    }
       }while (valid == false); 
    }
  
    public static String fileInput (String args) throws FileNotFoundException{ 
        
        Scanner fileInput;
                fileInput = new Scanner (new File (args)); 
        
        String data = " "; 
        
        while (fileInput.hasNextLine())
        {
            data = fileInput.nextLine();    
        }
        
        fileInput.close (); 
        
        return data;
    }  

    public static void adminPasswordOutput (String args) throws IOException {   
       
        FileWriter fileOutput = new FileWriter ("admin.dat"); 
        String hashPass, password;
        
        password = args;
        hashPass = Utility.getHash(password); 
        fileOutput.write (hashPass);
        fileOutput.close(); 
    }

    public static boolean samePassword (String newPass, String fileName) throws IOException 
    {
        Scanner fileInput;
        fileInput = new Scanner (new File (fileName)); 
        
        String temp, hashedPass;
        
        temp = fileInput.nextLine(); 
        hashedPass = Utility.getHash(newPass);
        
        if (temp.equals(hashedPass))
            return false; 
        else 
            return true; 
        
    }
}
