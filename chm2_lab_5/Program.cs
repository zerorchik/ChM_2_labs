using System;

namespace chm2_lab_5
{
    class Program
    {
        static void Main(string[] args)
        {
            Console.OutputEncoding = System.Text.Encoding.Default;
            const int n = 5;
            double[] x = { -2, 0, 2, 4, 6 };
            double[] y = new double[n];

            Console.WriteLine("Значення функції в точках інтерполяції:\n");
            for (int i = 0; i < n; i++)
            {
                y[i] = Function(x[i]);
                Console.WriteLine("x[{0}] = {1} \t y[{2}] = {3:f5}", i, x[i], i, y[i]);
            }

            Console.WriteLine("\nIнтерполяцiйний многочлен Лагранжа:");
            Lagrange(x, y, n);

            Console.WriteLine("\n\nIнтерполяцiя кубiчними сплайнами:\n");
            for (int i = 0; i < n; i++)
                Spline(x, y, n, x[i]);

        }

        static double Function(double x)
        {
            return Math.Pow(x, 2) / 15 + Math.Cos(x + 2);
        }

        static void Lagrange(double[] x, double[] y, int n)
        {
            Console.WriteLine();
            Console.Write("\t    (x - " + x[1] + ")(x - " + x[2] + ")(x - " + x[3] + ")(x - " + x[4] + ")   ");
            Console.Write("\t      (x + " + -x[0] + ")(x - " + x[2] + ")(x - " + x[3] + ")(x - " + x[4] + ")   ");
            Console.Write("\t      (x + " + -x[0] + ")(x - " + x[1] + ")(x - " + x[3] + ")(x - " + x[4] + ")   ");
            Console.Write("\t       (x + " + -x[0] + ")(x - " + x[1] + ")(x - " + x[2] + ")(x - " + x[4] + ")   ");
            Console.WriteLine("\t        (x + " + -x[0] + ")(x - " + x[1] + ")(x - " + x[2] + ")(x - " + x[3] + ")");
            Console.Write($"{y[0]:f5}"+" * -------------------------------- ");
            Console.Write($"{y[1]:f5}" + " * ---------------------------- ");
            Console.Write($"{y[2]:f5}"+" * ---------------------------- + ");
            Console.Write($"{y[3]:f5}" + " * ---------------------------- + ");
            Console.WriteLine($"{y[4]:f5}" + " * ---------------------------- ");
            Console.Write("\t  (" + x[0] + " - " + x[1] + ")(" + x[0] + " - " + x[2] + ")(" + x[0] + " - " + x[3] + ")(" + x[0] + " - " + x[4] + ")");
            Console.Write("\t      (" + x[1] + " + " + -x[0] + ")(" + x[1] + " - " + x[2] + ")(" + x[1] + " - " + x[3] + ")(" + x[1] + " - " + x[4] + ")");
            Console.Write("\t      (" + x[2] + " + " + -x[0] + ")(" + x[2] + " - " + x[1] + ")(" + x[2] + " - " + x[3] + ")(" + x[2] + " - " + x[4] + ")");
            Console.Write("\t       (" + x[3] + " + " + -x[0] + ")(" + x[3] + " - " + x[1] + ")(" + x[3] + " - " + x[2] + ")(" + x[3] + " - " + x[4] + ")");
            Console.Write("\t        (" + x[4] + " + " + -x[0] + ")(" + x[4] + " - " + x[1] + ")(" + x[4] + " - " + x[2] + ")(" + x[4] + " - " + x[3] + ")");
        }

        static double Spline(double[] X, double[] Y, int n, double x0)
        {
            double[] a = new double[n - 1];
            double[] b = new double[n - 1];
            double[] d = new double[n - 1];
            double[] h = new double[n - 1];

            double[,] A = new double[n - 1, n];

            double[] by = new double[n];

            for (int i = 0; i < n - 1; i++)
            {
                a[i] = Y[i];
                h[i] = X[i + 1] - X[i];
            }
            A[0, 0] = 1;
            A[n - 2, n - 2] = 1;
            for (int i = 1; i < n - 2; i++)
            {
                A[i, i - 1] = h[i - 1];
                A[i, i] = 2 * (h[i - 1] + h[i]);
                A[i, i + 1] = h[i];
                by[i] = 3 * (((Y[i + 1] - Y[i]) / h[i]) - ((Y[i] - Y[i - 1]) / h[i - 1]));
            }
            double[] c = Progon(A, by, n - 1);

            for (int i = 0; i < n - 1; i++)
            {
                if (i != n - 2)
                {
                    d[i] = (c[i + 1] - c[i]) / (3 * h[i]);
                    b[i] = ((Y[i + 1] - Y[i]) / h[i]) - h[i] * (c[i + 1] + 2 * c[i]) / 3;
                }
                else
                {
                    d[i] = (-1) * (c[i] / (3 * h[i]));
                    b[i] = ((Y[i] - Y[i - 1]) / h[i]) - ((2 * h[i] * c[i]) / 3);
                }
            }
            d[n - 2] = -c[n - 2] / (3 * h[n - 2]);
            b[n - 2] = ((Y[n - 1] - Y[n - 2]) / h[n - 2]) - 2 * h[n - 2] * c[n - 2] / 3;
            int m = 0;
            for (int i = 1; i < n; i++)
                if (x0 >= X[i - 1] && x0 <= X[i]) m = i - 1;

            double x = x0 - X[m];
            double y = a[m] + b[m] * x + c[m] * Math.Pow(x, 2) + d[m] * Math.Pow(x, 3);

            Console.WriteLine($"Коефiцiєнти для {y:f5}");
            Console.WriteLine($"a = {a[m]:f5}");
            Console.WriteLine($"b = {b[m]:f5}");
            Console.WriteLine($"c = {c[m]:f5}");
            Console.WriteLine($"d = {d[m]:f5}\n");

            return y;
        }

        static double[] Progon(double[,] A, double[] b, int n)
        {
            double[] K = new double[n];
            int n1 = n - 1;

            double y = A[0, 0];
            double[] a = new double[n];
            double[] b1 = new double[n];
            a[0] = -A[0, 1] / y;
            b1[0] = b[0] / y;
            for (int i = 1; i < n1; i++)
            {
                y = A[i, i] + A[i, i - 1] * a[i - 1];
                a[i] = -A[i, i + 1] / y;
                b1[i] = (b[i] - A[i, i - 1] * b1[i - 1]) / y;
            }
            K[n1] = b1[n1];
            for (int i = n1 - 1; i >= 0; i--)
                K[i] = a[i] * K[i + 1] + b1[i];
            return K;
        }

    }
}
