using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace VectoresListas
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            int size = getSize();
            estructura[] vectorEstr = new estructura[size]; 
        }

        private void button2_Click(object sender, EventArgs e)
        {
            int size = getSize();
            clase[] vectorClase = new clase[size];
            for (int i = 0; i < vectorClase.Length; i++)
            {
                vectorClase[i] = new clase();
            }
        }

        private void button3_Click(object sender, EventArgs e)
        {
            int size = getSize();
            List<estructura> listaEstr = new List<estructura>(size);
            List<clase> listaClase = new List<clase>(size);
        }

        private int getSize()
        {
            return int.Parse(textBox1.Text);
        }
    }

    class clase
    {
        int miInt;
        float miFloat;
    }

    struct estructura
    {
        int miInt;
        float miFloat;
    }
}
