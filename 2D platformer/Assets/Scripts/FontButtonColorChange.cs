using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using TMPro;

public class FontButtonColorChange : MonoBehaviour
{
    [SerializeField] private TMP_Text Text;
    [SerializeField] private Image _image;

    private Color _defaultFontColor;
    private void Awake()
    {
        _defaultFontColor = Text.color;
    }
    private void OnMouseEnter()
    {
        Text.color = _image.color;
    }
    private void OnMouseExit()
    {
        Text.color = _defaultFontColor;
    }
    private void OnMouseDown()
    {
        Text.color = _defaultFontColor;
    }

}
