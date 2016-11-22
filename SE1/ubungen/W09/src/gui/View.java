package gui;

import java.util.*;
import javax.swing.*;

import domain.Count;

public class View extends JFrame implements Observer {
    private JButton btn;

    public View(Count model) {
        btn = new JButton("" + model.getValue());
        btn.addActionListener(new IncListener(model));
        add(btn);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        pack();
        setVisible(true);
        model.addObserver(this);
    }

    public void
    update(Observable model, Object arg) {
        btn.setText("" + ((Count) model).getValue());
    }
}