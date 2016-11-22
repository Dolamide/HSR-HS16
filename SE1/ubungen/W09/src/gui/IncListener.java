package gui;

import domain.Count;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

/**
 * Created by rzi on 17.11.16.
 */
public class IncListener implements ActionListener {
    private Count model;

    public IncListener(Count model) {
        this.model = model;
    }

    @Override
    public void actionPerformed(ActionEvent e) {
        model.increment();
    }
}
