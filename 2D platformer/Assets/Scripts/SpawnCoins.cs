using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class SpawnCoins : MonoBehaviour
{
    [SerializeField] private GameObject _template;

    private void Start()
    {
        GameObject newObject = Instantiate(_template, new Vector3(0.7958186f, -1.03f, 0), Quaternion.identity);
    }

}


