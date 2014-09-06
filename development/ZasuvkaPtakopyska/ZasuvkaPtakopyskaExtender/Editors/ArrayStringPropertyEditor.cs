﻿using System;
using System.Collections.Generic;

namespace ZasuvkaPtakopyskaExtender.Editors
{
    [PtakopyskPropertyEditor("@ArrayString")]
    public class ArrayStringPropertyEditor : CollectionPropertyEditor<string>
    {
        public ArrayStringPropertyEditor(Dictionary<string, string> properties, string propertyName)
            : base(
            properties,
            propertyName,
            CollectionPropertyEditorUtils.CollectionType.JsonArray,
            (pd, pn) => new String_PropertyEditor(pd, pn)
            )
        {
        }
    }
}
