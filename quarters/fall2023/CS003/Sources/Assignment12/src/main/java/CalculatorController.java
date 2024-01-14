package main.java;

import javafx.fxml.FXML;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.input.MouseEvent;

import java.util.Stack;

public class CalculatorController {
    private Stack<Double> valueStack = new Stack<>();
    private String lastOperator = "";

    private boolean decimalPlaced = false;
    private boolean queuedClear = false;

    @FXML
    private Label display;

    @FXML
    void handle_button(MouseEvent event) {
        Button clicked = (Button) event.getSource();

        switch (clicked.getText()) {
            case "AC":
                valueStack.clear();
                ClearScreen();
                decimalPlaced = false;
                break;
            case "C":
                ClearScreen();
                break;
            case "+/-":
                String text = display.getText();
                if (!text.isBlank()) {
                    if (text.charAt(0) == '-') {
                        display.setText(text.substring(1));
                    } else {
                        display.setText("-" + text);
                    }
                }
                break;
            case "√":
                storeCurrentValue();
                display.setText(Double.toString(Math.sqrt(valueStack.pop())));
                break;
            case "eˣ":
                storeCurrentValue();
                display.setText(Double.toString(Math.exp(valueStack.pop())));
                break;
            case "log":
                storeCurrentValue();
                display.setText(Double.toString(Math.log(valueStack.pop())));
                break;
            case "Γ":
                storeCurrentValue();
                display.setText(Double.toString(MathFunctions.gamma(valueStack.pop())));
                break;
            case "ζ":
                storeCurrentValue();
                display.setText(Double.toString(MathFunctions.zeta(valueStack.pop())));
                break;
            case "+":
                storeCurrentValue();
                lastOperator = "+";
                break;
            case "-":
                storeCurrentValue();
                lastOperator = "-";
                break;
            case "×":
                storeCurrentValue();
                lastOperator = "×";
                break;
            case "÷":
                storeCurrentValue();
                lastOperator = "÷";
                break;
            case "xʸ":
                storeCurrentValue();
                lastOperator = "xʸ";
                break;
            case "=":
                storeCurrentValue();
                display.setText(Double.toString(CalculateDiadic()));
                break;
            case ".":
                if (decimalPlaced) {
                    break;
                }

                if (!decimalPlaced) {
                    decimalPlaced = true;
                }
            default:
                display.setText(display.getText() + clicked.getText());
        }

    }

    private void ClearScreen() {
        display.setText("");
    }

    private double CalculateDiadic() {

        if (valueStack.isEmpty())
        {
            return 0;
        }

        double value1 = valueStack.pop();
        double value2 = valueStack.pop();

        double result = 0;

        switch (lastOperator) {
            case "+":
                result = value1 + value2;
                break;
            case "-":
                result = value2 - value1;
                break;
            case "×":
                result = value1 * value2;
                break;
            case "÷":
                result = value2 / value1;
                break;
            case "xʸ":
                result = Math.pow(value2, value1);
                break;
        }

        lastOperator = "";

        return result;
    }

    private void storeCurrentValue() {
//        queuedClear = true;
        valueStack.push(Double.parseDouble(display.getText()));
        decimalPlaced = false;
        ClearScreen();
    }

}
