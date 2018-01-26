/*
* CSCI213 Assignment 4
* --------------------------
* File name: FPGServer.java
* Author: Chang Qi Jia
* Student Number: 5280618
* Description: GUI for the server
*/

import java.io.*; 
import java.util.*; 
import java.net.*; 
import javax.swing.*; 
import java.awt.event.*; 
import java.awt.*; 

public class FPGServer {
    
    private JFrame frame; 
    private JPasswordField passwordF; 
    private JTextField portNo; 
    private JComboBox playerNo;
    private JPanel bigPanel; 
    private JLabel player1; 
    private JLabel connection1; 
    private JLabel player2; 
    private JLabel connection2; 
    private JLabel player3; 
    private JLabel connection3; 
    private int noOfPlayers; 
    private BroadCaster bc ; 
    private WaitScreen screen; 
    
    public static void main (String [] args) {
        new FPGServer().run(); 
    }
    
    public void run () 
    {
        adminLogin (); 
    }
    
    public void adminLogin () 
    {
       frame = new JFrame ("Admin");
       frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE); 
       
       JPanel panel = new JPanel ();
       panel.setPreferredSize (new Dimension (275,100));
       
       JLabel label = new JLabel ("Password");
       passwordF= new JPasswordField (15);
       JButton Login = new JButton ("Login"); 
       
       Login.addActionListener (new LoginButtonListener ());
       
       panel.add (label); 
       panel.add (passwordF); 
       panel.add (Login);
       frame.add (panel); 
       
       frame.setPreferredSize (new Dimension (275,125));
       frame.pack();
       frame.setVisible (true);
    }

    private class LoginButtonListener implements ActionListener 
    {
        public void actionPerformed (ActionEvent e) 
        {
            String password = new String (passwordF.getPassword());
            loginCallBack (password); 
        }
    }
    
    public void loginCallBack (String password)
    {
        boolean success = false; 
        
        password = Utility.getHash (password); 
        
        success = checkLogin (password); 
        
        if (success == true)
            {
  
                frame.setVisible (false);
                frame.dispose(); 
                serverMenu (); 
            } 
        else
            {
                frame.setVisible (false); 
                printMessage ("Failed To Login!");
            }
    }
    
    public boolean checkLogin (String password)
    {
        boolean login = false; 
        Scanner fileInput = null; 
        String rightPass; 
        
        try {
           
                fileInput = new Scanner (new File ("admin.dat")); 
            }
        
        catch (FileNotFoundException ex)
        {  
                    System.out.print ("Error in locating file, please make sure the file <admin.dat> is available\n");
                    System.exit (-1);
        }
        
        rightPass = fileInput.nextLine() ; 
        
        if (rightPass.equals (password))
            login = true;
        
        return login;
    }
    
    public void printMessage (String msg)
    {
        frame = new JFrame ("Message");
        JPanel panel = new JPanel (); 
        JLabel label = new JLabel (msg); 
        label.setPreferredSize (new Dimension (225, 25));
        label.setHorizontalAlignment (SwingConstants.CENTER);
        
        JButton exit = new JButton ("Okay");
        
        exit.addActionListener (new LogoutButtonListener());
        
        panel.add (label); 
        panel.add (exit); 
        
        frame.add (panel);
        frame.setPreferredSize (new Dimension (250,125));
        frame.pack(); 
        frame.setVisible (true); 
        
    }
    
    private class LogoutButtonListener implements ActionListener 
    {
        public void actionPerformed (ActionEvent e) 
        {
            System.exit(0);
        }
    }
    
    public void serverMenu () 
    {
        frame = new JFrame ("Game Server");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE); 
        
        String [] noOfPlayer = {"1", "2", "3"};
        
        JPanel panel = new JPanel (); 
        
        JLabel port = new JLabel ("Port");
        portNo = new JTextField (15);
        
        JLabel players = new JLabel ("No. of Player(s):");
        playerNo = new JComboBox (noOfPlayer);
        
        JButton startGame = new JButton ("Start Game Server");
        startGame.addActionListener (new StartGameButtonListener());
        
        panel.add (port);
        panel.add (portNo);
        panel.add (players); 
        panel.add (playerNo); 
        panel.add (startGame);
        
        frame.add (panel); 
        frame.setPreferredSize (new Dimension (275,200));
        frame.pack (); 
        frame.setVisible (true); 
  
    }
    
    private class StartGameButtonListener implements ActionListener 
    {
        public void actionPerformed (ActionEvent e) 
        {
            String portNum = portNo.getText(); 
            
            String playerNum = (String) playerNo.getSelectedItem(); 
          
            startGameCallBack (portNum, playerNum);
        }
    }
    
    public void startGameCallBack (String portNum, String playerNum)
    {
        frame.setVisible (false); 
        
        int port ; 
        int noPlayer; 
        
        port = Integer.parseInt (portNum); 
        
        noPlayer = Integer.parseInt (playerNum);
        this.noOfPlayers = noPlayer; 
         
        bc = new BroadCaster (noPlayer); 
        newWaitScreen (port, noPlayer); 


    }
    
    public void newWaitScreen (int portNum, int noOfPlayer)
    {
        frame = new JFrame ("Game Server");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE); 
        
        bigPanel = new JPanel ();
        bigPanel.setPreferredSize (new Dimension (200, 300));
        
        JLabel label = new JLabel ("Listening to port: " + portNum);
        JPanel portLabel = new JPanel ();
        portLabel.add (label);
        bigPanel.add (portLabel); 
        
        JPanel panel1 = new JPanel (); 
        panel1.setPreferredSize (new Dimension (200, 30));
        
        player1 = new JLabel ("Player 1");
        connection1 = new JLabel ("Waiting for connection...");
        panel1.add (player1);
        panel1.add (connection1);
        bigPanel.add (panel1); 
               
        if (noOfPlayer > 1)
        {
            player2 = new JLabel ("Player 2");
            connection2 = new JLabel ("Waiting for connection...");
            
            JPanel panel2 = new JPanel (); 
            panel2.setPreferredSize (new Dimension (200, 30));
            panel2.add (player2);
            panel2.add (connection2); 
            
            bigPanel.add (panel2); 
        }
        
        if (noOfPlayer > 2)
        {
            player3 = new JLabel ("Player 3");
            connection3 = new JLabel ("Waiting for connection...");
            JPanel panel3 = new JPanel (); 
            panel3.setPreferredSize (new Dimension (200, 30));
            panel3.add (player3);
            panel3.add (connection3); 
            
            bigPanel.add (panel3); 
        }
       
       frame.add (bigPanel);
       bigPanel.setVisible (true); 
       
       frame.setPreferredSize (new Dimension (275,300));
       frame.pack(); 
       frame.setVisible (true); 
       
       frame.repaint(); 
       frame.revalidate(); 
       
       screen = new WaitScreen (portNum, noOfPlayer, this, bc);
       
    }
    
    public void updateScreen (String username, int playerNo)
    {
        if (playerNo == 1)
            {
                player1.setText ("Player 1: "+ username);
                connection1.setText ("Connected. Waiting for other players...");
            }
        else if (playerNo == 2)
            {
                player2.setText ("Player 2: "+ username);
                connection2.setText ("Connected. Waiting for other players...");
            }
        else if (playerNo == 3)
            {
                player3.setText ("Player 3: "+ username);
                connection3.setText ("Connected. Waiting for other players...");
            }    
              
        if (noOfPlayers == playerNo)
        {
            frame.setVisible (false); 
        }
        
        screen.addToBc(username, playerNo);
    }
}
