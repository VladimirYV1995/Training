using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Xml;
using System.IO;

namespace UIRS._3
{
    public partial class Form1 : Form
    {
        int amount;        
        SolidBrush mainBrush;               
        List<String> ProcentList = new List<String>();            
        List<String> StatusList= new List<String>();
        List<SolidBrush> BrushesList = new List<SolidBrush>();
        
        public Form1()
        {
            InitializeComponent();
        }
        //private void XMLReader()        
        private void Loadfile_Click(object sender, EventArgs e)
        {
            OpenFileDialog openFileDiolog = new OpenFileDialog();//"C:/data/XMLFile1.xml"
            openFileDiolog.Filter = "(*.xml)|*.xml";
            if (openFileDiolog.ShowDialog() == DialogResult.OK)
            {
                XmlTextReader xmlReader = new XmlTextReader(openFileDiolog.FileName); //экземпляр объекта, обеспечивает механизм чтения XML
                while (xmlReader.Read())//Метод Read последовательно перемещается по XML-файлу до достижения конца файла,
                {
                    switch (xmlReader.Name)
                    {
                        case ("signature"):
                            label.Text = xmlReader["signature"];//signature - имя узла в xml файле
                            Loadfile.Text = xmlReader["signature"];
                        continue;
                        case ("amountofsectors"):
                        amount = Int32.Parse(xmlReader["amountofsectors"]);
                        label.Text = xmlReader["amountofsectors"];
                        //continue;
                        //case ("condition"):
                       // StatusList.Add(xmlReader["status"]);
                        //ProcentList.Add(xmlReader["procent"]);
                        break;
                    }
                }
                xmlReader.Close();
            }
        }
        
        private void MakeDiagram_Click(object sender, EventArgs e)
        {
            Random r = new Random(DateTime.Now.Millisecond); 
            
            for (int i = 0; i < amount; i++)            
            {
                mainBrush = new SolidBrush(Color.FromArgb(r.Next(255), r.Next(255), r.Next(255), r.Next(255)));
                BrushesList.Add(mainBrush);                
            }           
            panel.Paint += new PaintEventHandler(DiogramPaint);
            panel.Invalidate();
        }
       
        private void button1_Click(object sender, EventArgs e)
        {
            SolidBrush SectorChangeColor = new SolidBrush(Color.Transparent);
            ColorDialog colorDlg = new ColorDialog();
            
            if (colorDlg.ShowDialog() == DialogResult.OK)
            {
                SectorChangeColor.Color = colorDlg.Color;
                BrushesList[dataGridView.SelectedRows[0].Index] = SectorChangeColor;
                panel.Invalidate();
            }     
        }              
        
        private void DiogramPaint(object sender, PaintEventArgs e)
        {
            int i;
            float x, y, w, h, L1, L2, Kr, da, angle = 0, k = 0.15F;      
            
            Pen blackPen = new Pen(Color.Black, 4);
            SolidBrush blackBrush = new SolidBrush(Color.Black);
            SolidBrush panelBrush = new SolidBrush(panel.BackColor);
            Graphics G;
            Bitmap color;
            Font font = new Font("Arial", 8);
            PointF pt1 = new PointF(panel.Size.Width / 2, panel.Size.Height / 2);
            PointF pt2 = new PointF((1 - k) * panel.Size.Width, panel.Size.Height / 2);
            PointF pt3 = new PointF();

            x = k * panel.Size.Width;
            y = k * panel.Size.Height;
            w = (1 - 2 * k) * panel.Size.Width;
            h = (1 - 2 * k) * panel.Size.Height;
            L1 = pt2.X - pt1.X;
            L2 = pt1.X - k / 2 * panel.Size.Width;
            Kr = (float)3.14 / 180;

            dataGridView.Rows.Clear();
            e.Graphics.FillRectangle(panelBrush, 0, 0, panel.Size.Width, panel.Size.Height);

            for ( i = 0; i < amount; i++)
            {
                color = new Bitmap(100, 100);
                G = Graphics.FromImage(color);
                G.FillRectangle(BrushesList[i], new Rectangle(0, 0, 100, 100));
                dataGridView.Rows.Add(color, StatusList[i]);
                
                e.Graphics.DrawLine(blackPen,pt1,pt2); 
               
                da = (float)(3.6 * (Convert.ToDouble(ProcentList[i])));
               
                e.Graphics.FillPie(BrushesList[i], x, y, w, h, angle, da);
                
                angle += da;
                
                pt2.X = pt1.X + L1 * (float)Math.Cos(angle * Kr);
                pt2.Y = pt1.Y + L1 * (float)Math.Sin(angle * Kr);

                pt3.X = pt1.X + L2 * (float)Math.Cos((angle - da / 2) * Kr) - 20;
                pt3.Y = pt1.Y + L2 * (float)Math.Sin((angle - da / 2) * Kr);                
                e.Graphics.DrawString(ProcentList[i] + "%", font, blackBrush, pt3.X, pt3.Y);
            }    
            e.Graphics.DrawEllipse(blackPen, x, y, w, h);          
        }

        private void Form1_Load(object sender, EventArgs e)
        {

        }

        
          
             
    }
}
