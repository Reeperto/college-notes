package main.java;

public class MathFunctions {
    private static final int ITERATIONS = 5000;
    public static double zeta(double s) {
        double sum = 0;

        if (s > 1) {
            for (int i = 1; i < ITERATIONS; ++i) {
                sum += 1.0 / Math.pow(i, s);
            }

            return sum;
        } else if (s <= 1) {
            for (int i = 1; i < ITERATIONS; ++i) {
                sum += 1.0 / Math.pow(i, 1 - s);
            }

            return sum * gamma(1 - s) * Math.sin(Math.PI * s / 2.0) * Math.pow(2, s) * Math.pow(Math.PI, s - 1);
        }

        return Double.NaN;
    }

    static double logGamma(double x) {
        double tmp = (x - 0.5) * Math.log(x + 4.5) - (x + 4.5);
        double ser = 1.0 + 76.18009173    / (x + 0)   - 86.50532033    / (x + 1)
                + 24.01409822    / (x + 2)   -  1.231739516   / (x + 3)
                +  0.00120858003 / (x + 4)   -  0.00000536382 / (x + 5);
        return tmp + Math.log(ser * Math.sqrt(2 * Math.PI));
    }
    static double gamma(double x) {
        return Math.exp(logGamma(x));
    }
}
