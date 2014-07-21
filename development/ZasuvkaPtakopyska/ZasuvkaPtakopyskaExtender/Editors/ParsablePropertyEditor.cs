﻿using System;
using MetroFramework.Controls;
using System.Windows.Forms;
using System.Reflection;

namespace ZasuvkaPtakopyskaExtender.Editors
{
    public abstract class ParsablePropertyEditor<T> : PropertyEditor<T>
    {
        private MetroTextBox m_textBox;

        public ParsablePropertyEditor(object propertyOwner, string propertyName, T defaultValue)
            : base(propertyOwner, propertyName, defaultValue)
        {
            m_textBox = new MetroTextBox();
            MetroSkinManager.ApplyMetroStyle(m_textBox);
            m_textBox.Text = Value.ToString();
            m_textBox.Width = Width;
            m_textBox.Top = Height;
            m_textBox.Anchor = AnchorStyles.Top | AnchorStyles.Left | AnchorStyles.Right;
            m_textBox.TextChanged += new EventHandler(m_textBox_TextChanged);
            Controls.Add(m_textBox);

            Height += m_textBox.Height;
        }

        private void m_textBox_TextChanged(object sender, EventArgs e)
        {
            MethodInfo method = null;
            try { method = typeof(T).GetMethod("Parse", new Type[] { typeof(string) }); }
            catch { }
            if (method == null)
                return;

            T v = Value;
            try { v = (T)method.Invoke(null, new object[] { m_textBox.Text }); }
            catch { }
            Value = v;
        }
    }
}